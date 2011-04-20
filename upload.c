#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

void output_err(char* err)
{
	printf("Content-Type: text/plain\n\n");
	printf("%s\n", err);
}

int get_content_len()
{
	int len;
	char* ret = getenv("CONTENT_LENGTH");
	if(ret == NULL)
	{
		output_err("content len is NULL");
		exit(0);
	}

	len = atoi(ret);
	if(len == 0)
	{
		output_err("content len is 0");
		exit(0);
	}

	return len;
}

int main(int argc, char* argv[])
{
	int content_len = get_content_len();
	char buf[1024];
	int bound_len;
	char* file_type;
	char* file_name;
	char* tmp;
	char path_name[256];
	int file_fd;
	int ret;
	
	// first line is boundry 
	fgets(buf, sizeof(buf), stdin);
	bound_len = strlen(buf); // greater than boundry 4
	content_len -= bound_len;

	fgets(buf, sizeof(buf), stdin);
	content_len -= strlen(buf);
	/* get file type  */
	file_type = strstr(buf, "name=");
	file_type += (strlen("name=")+1);
	file_name = strstr(file_type, "\"");
	*file_name = 0;

	/* get file name */
	file_name++;
	file_name = strstr(file_name, "filename=");
	file_name += (strlen("filename=")+1);
	tmp = strstr(file_name, "\"");
	*tmp = 0;

	// open file
	sprintf(path_name, "%s/%s", file_type, file_name);
	file_fd = open(path_name, O_CREAT|O_TRUNC|O_RDWR, 0644);
	if(file_fd < 0)
	{
		output_err("Can not open file");
		exit(0);		
	}

	// drop one line
	fgets(buf, sizeof(buf), stdin);
	content_len -= strlen(buf);
	fgets(buf, sizeof(buf), stdin);
	content_len -= strlen(buf);
	content_len -= (bound_len+4); // content_len = file_len;

	while(content_len > 0)
	{
		if(content_len>1024)
			ret = fread(buf, 1, 1024, stdin);
		else 
			ret = fread(buf, 1, content_len, stdin);
		write(file_fd, buf, ret);
		content_len -= ret;
	}
	close(file_fd);
	output_err("file transfer success");

	return 0;
}
