#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *key;
    int n;
    char **trans;
} word_t;


void display(word_t *p)
{
    printf("%s\n",p->key);
    int i;
    for (i = 0; i < p->n; i++) 
    {
        printf("%s\n",p->trans[i]);
    }
}

void dict_free(word_t *p)
{
    int i;
    for (i = 0; i < p->n; i++) 
    {
       if(p->trans[i] != NULL)
        free(p->trans[i]);
    }  
    free(p->trans);
    if(p->key != NULL)
    free(p->key);
    p->n =0;
    free(p);
}


int main(int argc, const char *argv[])
{
    FILE *fp = fopen("1dict.txt", "r");
    char buf[100];

       rewind(fp);
     word_t *p = malloc(sizeof(word_t));

     if(fgets(buf,100,fp) != NULL)
        {
            printf("%s",buf);
        }
      int len = 0;
      len = strlen(buf) ;
      if (buf[len - 1] == '\n') 
      {
          buf[len - 1] = '\0';
      }
      p->key = malloc(sizeof(char)*(len - 1));
        strncpy(p->key, &buf[1], len);
        printf("%s\n",p->key);
        



        int i = 0;
        int counter = 1;
        char *brok = NULL;
     if(fgets(buf,100,fp) != NULL)
        {
            printf("%s",buf);
        }
      len = strlen(buf) ;
      if (buf[len - 1] == '\n') 
      {
          buf[len - 1] = '\0';
      }
      while (buf[i++] != '\0') 
      {
          if(buf[i] == '@')
          counter++;
      }
      
      printf("counter %d\n",counter);
    p->n = counter; 
    char *bb = &buf[6];
    
    p->trans = (char **)malloc(sizeof(char *) * counter);      
    if(p->trans == NULL){
        perror("error");
        exit(0);
    }
    for (i = 0; i < counter; i++) 
    {
        brok = strsep(&bb, "@");
        printf("%d\n",strlen(brok));

        p->trans[i] = (char *)malloc( 15 );
        if(p->trans[i] == NULL){
            perror("error");
            exit(0);
        }
        
     
        strncpy(p->trans[i], brok, len);
        printf("%s\n",p->trans[i]);
        
    }
    //display(p);
    dict_free(p);
    free(fp); 
    return 0;
}
