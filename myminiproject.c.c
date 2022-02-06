#include<stdio.h>
#include<stdlib.h>          //header file
#include<string.h>
#include<conio.h>
#include<windows.h>
struct book         //Book type structure
{
    int id;
    char name[20],author[20];
    float price;
};
COORD cord={0,0};           //predefine coord structure

void gotoxy(int x, int y)       //functio to set coordinate
{
    cord.X=x;
    cord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cord);
}
void insert()                   //function to inserrt record.
{
    system("cls");
    struct book b;
    FILE *fp;               //declare file type pointer
    fp=fopen("myfile.txt","ab");        //open file in append and binary mode
    if(fp==NULL)            //check, is file is open or not.
    {
        fp=fopen("myfile.txt","wb");        //if file not open then create open it.
        if(fp==NULL)
        {
            printf("unable to open file.");
            exit(0);
        }
    }
    printf("enter book id:");
    scanf("%d",&b.id);
    getchar();
    if(b.id<0)
        b.id=-b.id;
    fflush(stdin);                              //take inputs from user.
    printf("enter book name:");
    gets(b.name);

    printf("enter book author:");
    gets(b.author);
    printf("enter book price:");
    scanf("%f",&b.price);
    fwrite(&b,sizeof(b),1,fp);          //function to write data into file.
    fclose(fp);                 //close file.
}               //end of insert function
void delete()                   //function to delete record from file.
{
    system("cls");          //clear screen
    FILE *fp,*ft;               //create file pointer
    struct book b;              //declare book type object
    char key[20];int flag=0;        //local variable
    fp=fopen("myfile.txt","rb");        //open file
    if(fp==NULL)
        printf("\nSorry, file does not exist.");
    else
    {
        ft=fopen("temp.txt","wb");
        if(ft==NULL)
            printf("Sorry, unable to delete record.");
        else
        {
            fflush(stdin);
            printf("enter name of book to be delete: ");        //take input from user
            gets(key);
            while(fread(&b,sizeof(b),1,fp))
            {
                if(strcmp(b.name,key)==0)
                {
                    printf("%d\t%s\t%s\t%0.2f\n",b.id,b.name,b.author,b.price);
                    flag=1;

                }
                if(strcmp(b.name,key)!=0)
                {
                    fwrite(&b,sizeof(b),1,ft);
                }
            }
            fclose(fp);
            fclose(ft);
            if(flag==0)
                printf("\nSorry, record not found.");
            else
            {
                remove("myfile.txt");           //remove file
                rename("temp.txt","myfile.txt");            //rename temprary file to main file
                printf("Record deleted successfully.\a");
            }
        }
    }
    printf("\n\npress any key continue. . .");
    getch();
}                   //end of delete function
void display()              //function to display record from file
{
    FILE *fp;int flag=0,count=0;
    struct book b;
    system("cls");
    fp=fopen("myfile.txt","r");
    if(fp==NULL)
        printf("Sorry,file does not exist.");
    else
    {
        printf("\n\n\n\t\t\tBook store\n");
        printf("----------------------------------------------------------------\n");
        printf("Book_id\tBook_name\tBook_author\t\tBook_price\n");
        printf("----------------------------------------------------------------\n");
        while(fread(&b,sizeof(b),1,fp))             //while loop
        {
            printf("%d\t%s\t\t%s\t\t%0.2f\n",b.id,b.name,b.author,b.price);
            flag=1;
            count++;
        }
        fclose(fp);
        if(flag==0)
            printf("Sorry, file is empty.\n");
        else
            printf("\nTotal record %d.",count);
    }
    printf("\n\npress any key continue. . .");
    getch();
}               //end of function display
void search()          //function to search record from file
{
    system("cls");
    FILE *fp;
    char key[20];int flag=0;
    struct book b;
    fp=fopen("myfile.txt","r");
    if(fp==NULL)
        printf("Sorry, file is not found");
    else
    {
        fflush(stdin);
        printf("Enter book to be search: ");
        gets(key);
        printf("boook id\tbook nmae\tbook author\t\tprice\n");
         printf("----------------------------------------------------------------\n");
        while(fread(&b,sizeof(b),1,fp))         //while loop
        {
            if(strcmp(b.name,key)==0)   //compare record
            {
                printf("%d\t\t%s\t\t%s\t%0.2f\n",b.id,b.name,b.author,b.price);
                flag=1;
            }
        }
        if(flag==0)
            printf("\nSorry,record not found.\n");
    }
    fclose(fp);
    printf("\npress any key to continue. . .");
    getch();
}                   //end of function search
void update()              //function to update record
{
    system("cls");
     FILE *fp,*ft;
    struct book b;
    long int size=sizeof(b);
    char key[20];int flag=0;
    fp=fopen("myfile.txt","rb");
    if(fp==NULL)
    {
        printf("Sorry,file does not exist.");
        exit(0);
    }
    else
    {
        ft=fopen("temp.txt","wb");
        if(ft==NULL)
            {
                printf("unable to open file.");
                exit(0);
            }
            else
            {
             fflush(stdin);
                printf("enter name of book to be update: ");
               scanf("%19s",key);// gets(key);
                while(fread(&b,sizeof(b),1,fp))         //while loop
                {
                    if(strcmp(b.name,key)==0)
                    {
                        printf("enter new book id:");
                        scanf("%d",&b.id);
                        if(b.id<0)
                            b.id=-b.id;
                        fflush(stdin);
                        printf("enter new book name:");         //take data from user
                        gets(b.name);
                        printf("enter new book author:");
                        gets(b.author);
                        printf("enter new book price:");
                        scanf("%f",&b.price);
                       // fseek(fp,-size,SEEK_CUR);
                        fwrite(&b,size,1,ft);
                        flag=1;
                    }
                    else
                    {
                        fwrite(&b,size,1,ft);
                    }
                }
                fclose(fp);
                fclose(ft);
                if(flag==0)
                {
                    printf("\nSorry,record not found.");
                }
                else
                {
                    remove("myfile.txt");
                    rename("temp.txt","myfile.txt");
                    printf("\nupdate successfully.");
                }
            }
    }
    printf("\npress any key to continue. . .");
    getch();
}                   //end of function update
void drop()         //function to delete file permanently
{
    FILE *fp;
    fp=fopen("myfile.txt","r");
    if(fp==NULL)
     {
         printf("Sorry,file does not exist.");
     }
    else
    {
        fclose(fp);
        remove("myfile.txt");
        printf("file delete successfully.");
    }
    printf("\n\npress any key to continue. . .");
    getch();
}                           //end of function drop
void trancate()         //function to delete all record from file
{
    FILE *fp;
    fp=fopen("myfile.txt","r");     //open file
    if(fp==NULL)        //check whether file is open or not
        printf("Sorry,file dose not exist.");
    else
    {
        fclose(fp);         //close file
        fp=fopen("myfile.txt","w");     //open file in write mode
        fclose(fp);                 //close file
        printf("file trancate successfully.");
    }
    printf("\n\npress any key to continue. . .");
    getch();
}                   //end of function truncate
void sleep();       //sleep function
void main()         //main function
{
    int choice;         //local variable declaration
    system("color 3f");     //change screen color
    gotoxy(40,16);          //set cursor position
    printf("WELCOME!");
    gotoxy(80,25);          //set cursor position
    sleep(5);           //sleep system for few second
    system("cls");          //clear screen
    gotoxy(40,10);              //set cursor position
    printf("BOOK STORE");
    gotoxy(30,11);              //set cursor position
    printf("--------------------------------------");
    gotoxy(60,22);              //set cursor position
    printf("Developer:Ritur@j prajapati.\n");
    gotoxy(0,25);           //set cursor position
    system("pause");        //pause system
    do              //do-while loop
    {
        system("cls");      //clear screen
        gotoxy(30,5);           //set cursor position
        printf("***BOOK STORE***");
        printf("\n1.Insert.\n\n2.Delete.\n\n3.Display.\n\n4.Update.\n\n5.Search.");
        printf("\n\n6.Drop.\t\tWARNNING:YOU WILL LOST YOUR DATA.");
        printf("\n\n7.Trucate.\tWARNNING:YOU WILL LOST YOUR DATA.");
        printf("\n\n0.Exit.");
        printf("\n\nEnter your choice: ");
        scanf("%d",&choice);            //take choice from user
        switch(choice)          //switch case
        {
            case 1:insert();break;
            case 2:delete();break;          //cases and function call
            case 3:display();break;
            case 4:update();break;
            case 5:search();break;
            case 6:drop();break;
            case 7:trancate();break;
            case 0:printf("\nThank you for using.");
                    printf("\nExit.");
                    printf("\n----------------------------***xxx***-------------------------------");
                    exit(0);
            default:printf("invalid choice.");
                    printf("\nplease, enter choice between 0-8.");
                    getch();
        }               //end of switch case
    }while(choice!=0);          //end of do while loop
}                   //end of main function
                //end of program
