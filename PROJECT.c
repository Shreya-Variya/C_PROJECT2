#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct student
{
    int r_no;
    char name[20];
    int m[5];
    int total;
    float per;
}s;

int empty()
{
    int c=0;
    FILE *fp;
    fp = fopen("originalfile.txt","r");
    while (fread(&s,sizeof(s),1,fp))
    {
        c=1;
    }
    fclose(fp);
    return c;
}

int avl(int rno)
{
    FILE *fp;
    fp = fopen("originalfile.txt","r");
    while (!feof(fp))
    {
        fread(&s,sizeof(s),1,fp);
        if(rno == s.r_no)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void printmenu()
{
    printf("\n******************** SELECT ANY ONE OPTION ********************");
    printf("\n\t\t\t1.INSERT.");
    printf("\n\t\t\t2.DISPLAY.");
    printf("\n\t\t\t3.UPDATE.");
    printf("\n\t\t\t4.DELETE.");
    printf("\n\t\t\t5.SORT.");
    printf("\n\t\t\t6.SEARCH BY NAME.");
    printf("\n\t\t\t7.SEARCH BY ROLL NUMBER.");
    printf("\n\t\t\t8.EXIT.");
}

void insert()
{
    FILE *fp;
    int i;
    fp = fopen("originalfile.txt","a");

    printf("Enter the roll number : ");
    scanf("%d",&s.r_no);
    printf("Enter the name : ");
    scanf("%s",s.name);
    s.total=0;
    for(i=0 ; i<5 ; i++)
    {
        printf("Enter the mark of subject %d : ",i+1);
        scanf("%d",&s.m[i]);

        s.total = s.total + s.m[i];
    }
    s.per = s.total / 5;

    fwrite(&s,sizeof(s),1,fp);

    fclose(fp);
}

void display()
{
    FILE *fp;
    fp = fopen("originalfile.txt","r");

    printf("\nRollNo\t\tName\t\tSub1\t\tSub2\t\tSub3\t\tSub4\t\tSub5\t\tTotal\t\tPercentage\n");
    while (fread(&s,sizeof(s),1,fp))
    {
        printf("\n%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f\n",s.r_no,s.name,s.m[0],s.m[1],s.m[2],s.m[3],s.m[4],s.total,s.per);
    }
    fclose(fp);
}

void update()
{
    int av,rno,c,i;
    FILE *fpo;
    FILE *fpt;

    printf("Enter the rollno you want to update : ");
    scanf("%d",&rno);

    av = avl(rno);
    if(av==0)
    {
        printf("\n%d rollno is not available.",rno);
    }
    else
    {
        fpo = fopen("originalfile.txt","r");
        fpt = fopen("tempfile.txt","w");
        while (fread(&s,sizeof(s),1,fpo))
        {
            if(s.r_no!=rno)
            {
                fwrite(&s,sizeof(s),1,fpt);
            }
            else
            {
                printf("\n1.UPDATE THE NAME.");
                printf("\n2.UPDATE THE MARKS.");
                printf("\n3.UPDATE BOTH NAME AND MARKS.");
                printf("\nEnter your choice : ");
                scanf("%d",&c);
                switch(c)
                {
                    case 1: 
                        printf("\nEnter the updated name : ");
                        scanf("%s",s.name);
                        break;

                    case 2:
                        s.total=0;
                        for(i=0 ; i<5 ; i++)
                        {
                            printf("Enter the mark of subject %d : ",i+1);
                            scanf("%d",&s.m[i]);
                            s.total = s.total + s.m[i];
                        }
                        s.per = s.total / 5;
                        break;

                    case 3:
                        printf("\nEnter the updated name : ");
                        scanf("%s",s.name);
                        s.total=0;
                        for(i=0 ; i<5 ; i++)
                        {
                            printf("Enter the mark of subject %d : ",i+1);
                            scanf("%d",&s.m[i]);
                            s.total = s.total + s.m[i];
                        }
                        s.per = s.total / 5;
                        break;

                    default:
                        printf("\nInvalid Selection.");
                        break;
                }
                fwrite(&s,sizeof(s),1,fpt);
            }
        }
        fclose(fpo);
        fclose(fpt);
        fpo = fopen("originalfile.txt","w");
        fpt = fopen("tempfile.txt","r");

        while (fread(&s,sizeof(s),1,fpt))
        {
            fwrite(&s,sizeof(s),1,fpo);
        }
        fclose(fpo);
        fclose(fpt);
        printf("RECORD UPDATED.");    
    }
}

void deletion()
{
    int rno,av;
    FILE *fpo;
    FILE *fpt;

    printf("Enter the rollno you want to delete : ");
    scanf("%d",&rno);

    av = avl(rno);
    if(av==0)
    {
        printf("\n%d rollno is not available.",rno);
    }
    else
    {
        fpo = fopen("originalfile.txt","r");
        fpt = fopen("tempfile.txt","w");
        while (fread(&s,sizeof(s),1,fpo))
        {
            if(s.r_no!=rno)
            {
                fwrite(&s,sizeof(s),1,fpt);
            }
        }
        fclose(fpo);
        fclose(fpt);
        fpo = fopen("originalfile.txt","w");
        fpt = fopen("tempfile.txt","r");

        while (fread(&s,sizeof(s),1,fpt))
        {
            fwrite(&s,sizeof(s),1,fpo);
        }
        fclose(fpo);
        fclose(fpt);
        printf("RECORD DELETED.");
    }
}

void sort()
{
    int count=0,a[count];
    int temp,i,j;
    FILE *fp;
    fp = fopen("originalfile.txt","r");
    while (fread(&s,sizeof(s),1,fp))
    {
        a[count] = s.r_no;
        count++;
    }

    for ( i = 0; i < count; i++)
    {
        for ( j = i+1; j < count; j++)
        {
            if(a[i]>a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    printf("\nRollNo\t\tName\t\tSub1\t\tSub2\t\tSub3\t\tSub4\t\tSub5\t\tTotal\t\tPercentage\n");
    for ( i = 0; i < count; i++)
    {
        rewind(fp);
        while (fread(&s,sizeof(s),1,fp))
        {
            if(a[i] == s.r_no)
            {
                printf("\n%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f\n",s.r_no,s.name,s.m[0],s.m[1],s.m[2],s.m[3],s.m[4],s.total,s.per);
            }
        }
    }
    fclose(fp);
}

void searchbyname()
{
    FILE *fp;
    char name[20];
    int c=0;

    printf("Enter the name you want to search : ");
    scanf("%s",name);

    fp = fopen("originalfile.txt","r");
    while (fread(&s,sizeof(s),1,fp))
    {
        if(strcmp(name,s.name)==0)
        {
            printf("\n%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f\n",s.r_no,s.name,s.m[0],s.m[1],s.m[2],s.m[3],s.m[4],s.total,s.per);
            c++;
        }
    }
    if(c==0)
    {
        printf("\nNO RECORD FOUNDED.");
    }
    else
    {
        printf("\n%d RECORD FOUNDED.",c);
    }
    fclose(fp);
}

void searchbyno()
{
    FILE *fp;
    int no,c=0;

    printf("Enter the rollno you want to search : ");
    scanf("%d",&no);

    fp = fopen("originalfile.txt","r");
    while (fread(&s,sizeof(s),1,fp))
    {
        if(no == s.r_no)
        {
            printf("\n%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f\n",s.r_no,s.name,s.m[0],s.m[1],s.m[2],s.m[3],s.m[4],s.total,s.per);
            c++;
        }
    }
    if(c==0)
    {
        printf("\nNO RECORD FOUNDED.");
    }
    else
    {
        printf("\n%d RECORD FOUNDED.",c);
    }
    fclose(fp);
}

int main()
{
    int choice,emp;
    do
    {
        printmenu();

        printf("\nEnter your choice : ");
        scanf("%d",&choice);
        printf("\n");

        switch (choice)
        {
            case 1:
                insert();
                break;
            
            case 2: 
                emp = empty();
                if(emp==0)
                {
                    printf("\nFILE IS EMPTY.\n");
                }
                else
                {
                    display();
                }
                break;

            case 3:
                update();
                break;

            case 4: 
                deletion();
                break;

            case 5:
                sort();
                break;

            case 6:
                searchbyname();
                break;

            case 7:
                searchbyno();
                break;

            case 8:
                printf("TNE END.");
                exit(1);
                break;

            default:
                printf("\nEnter correct choice.");
                break;   
        }
    } 
    while (choice!=8);
    
    return 0;
}
