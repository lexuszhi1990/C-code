#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sqlite3.h>
#include <stdlib.h>

void err_sys(const char *p)
{
    printf("%s\n", p);
    exit(0);
}

int recallback(void *p, int argc, char **argv, char **argvv)
{
    int i;
    *(int *)p = 0;
#if 0
    for (i = 0; i < argc; i++) {
        printf("%s = %s", argvv[i], 
                    argv[i]?argv[i]:"NULL");
    }
    putchar('\n');
#endif
    return 0;
}

int sql_check(const char *name, const char *pd)
{
    sqlite3 *db;
    char *err = NULL;
    int ret = 0;
    int empty = 1;
    const char *uname = name;
    const char *passwd = pd;
    char sql[1024];

    ret = sqlite3_open("./mytable.db", &db);
    if (ret != SQLITE_OK) {
        fputs(sqlite3_errmsg(db), stdout);
        fputs("\n", stdout);
        exit(1);
    }

    sprintf(sql, "select * from tuser where username=\"%s\" and password=\"%s\"", uname, passwd);

    ret = sqlite3_exec(db, sql, recallback, &empty, &err);
    if (ret != SQLITE_OK) {
          fputs(err, stdout);
        fputs("\n", stdout);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);

    return empty;
}

extern char **environ;
int main(int argc, const char *argv[])
{
    printf("Content-Type: text/plain\n\n");
    char *passwd;
    char *uname;
    char *env;
    env = getenv("REQUEST_METHOD");
    if (env) {
        if (strcmp(env, "post") != 0 && strcmp(env, "POST") != 0) {
            err_sys("method is not post");
        }
    }else {
        err_sys("env is NULL");
    }
    
    env = getenv("CONTENT_LENGTH");
    if(env == NULL) {
        err_sys("env is null");
    }
    int len = atoi(env);
    if (len == 0) {
        err_sys("len is zero");
    }
    char *buf = (char *)malloc(len + 1);
    buf[len] = 0;

    int i = 0;
    while( i != len){
        i += read(STDIN_FILENO, buf + i, len - i);
    }

    uname = strstr(buf, "username=");
    uname += strlen("username=");
    passwd = strstr(buf, "&");
    *passwd = '\0';
    passwd = strstr(passwd + 1, "password=");
    passwd += strlen("passwodr=");
#ifdef DEBUG
    printf("%s,%s\n", uname, passwd);
#endif
       
    if( sql_check(uname, passwd)){
    
        fputs("sorry ~the username is not exited or the password is wrong\n", stdout);
        exit(1);
    }else {
        printf("welcome come in\n");
    }

    return 0;
}
