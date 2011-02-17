stu read_stu(void)
{
    FILE *fp;
    int number = 0;
    char na[20];
    stu head = NULL;
    stu p = NULL;

    fp = fopen("tex.txt","t+");
    if (fp == NULL) 
    {
        fp = fopen("tex.txt","t+");
        stu_check(fp);
        fclose(fp);
        return ;
    }

    if (fscanf(fp , "%d%s", &number, na) != EOF) 
    {
        p = malloc(sizeof(struct student));
        stu_check(p);
        p->num = number;
        strncpy(p->name, na , 14);
        p->next = NULL;

        head = p;
    }
    while (fscanf(fp , "%d%s", &number, na) != EOF) 
    {
        p->next = malloc(sizeof(struct student));
        stu_check(p->next);
        p->next->num = number;
        strncpy(p->next->name, na , 14);
        p->next->next = NULL;

        p = p->next;
    }
    fclose(p);
}
