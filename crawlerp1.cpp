#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include<fstream>
#include <sstream>
#define maxurllength 100
#define maxurl 10
#define maxdepth 4
#define directory crawler_directory/
#define seedurl www.chitkara.edu.in
using namespace std;
int file_no=1;
struct URL
{
    char str[maxurllength];
    int depth;
};
struct node
{
    struct URL u;
    struct node *next;
    int isVisited;
    int key;
};
struct node *head=NULL;
class linklist
{
public:
    struct node* create(char *ptr22,int dd)
    {
        struct node *ptr=new struct node;
        strcpy(ptr->u.str,ptr22);
        ptr->u.depth=dd;
        ptr->isVisited=0;
        ptr->key=1;
        ptr->next=NULL;
        return ptr;
    }
    void inserttail(char *ptr,int dd)
    {
        struct node *temp,*t;
        temp=create(ptr, dd);
        if(head==NULL)
        {
            head=temp;
        }
        else
        {
            t=head;
            
            while(t->next!=NULL)
            {
                t=t->next;
            }
            t->next=temp;
            temp->next=NULL;
        }
    }
    int check(char *ptr)
    {
        struct node *temp=head;
        if(temp==NULL)
        {
            return 0;
        }
        while(temp!=NULL)
        {
            if(strcmp(ptr,temp->u.str)==0)
            {
                return 1;
            }
            temp=temp->next;
        }
        return 0;
    }
    void display()
    {
        struct node *temp=head;
        while(temp!=NULL)
        {
            printf("\n%s\n",temp->u.str);
            temp=temp->next;
        }
    }
};
void testDir(char *dir)
{
    struct stat statbuf;
    if ( stat(dir, &statbuf) == -1 )
    {
        fprintf(stderr, "-----------------\n");
        fprintf(stderr, "Invalid directory\n");
        fprintf(stderr, "-----------------\n");
        exit(1);
    }
    
    //Both check if there's a directory and if it's writable
    if ( !S_ISDIR(statbuf.st_mode) )
    {
        fprintf(stderr, "-----------------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
        fprintf(stderr, "-----------------------------------------------------\n");
        exit(1);
    }
    
    if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR )
    {
        fprintf(stderr, "------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. It isn't writable\n");
        fprintf(stderr, "------------------------------------------\n");
        exit(1);
    }
}
int atoi(char *str)
{
    int i=0,num,res=0;
    while(str[i]!='\0')
    {
        num=(str[i]-48);
        res=res*10+num;
        i++;
    }
    return res;
}
void safe_keeping_page(char *url)
{
    FILE *inputFile;
    char itostring[10];
    sprintf(itostring,"%d",file_no);
    char tempdir[100];
    strcat(tempdir,"crawler_directory/");
    strcat(tempdir,itostring);
    strcat(tempdir,".txt");
    inputFile=fopen(tempdir,"w");
    if(inputFile==NULL)
    {
        fprintf(stderr," ERROR OPENING FILE ");
    }
    else
    {
        char urlbuffer[1000]={0};
        strcat(urlbuffer,"wget -O ");
        strcat(urlbuffer,"~/desktop/crawler_directory/");
        strcat(urlbuffer,itostring);
        strcat(urlbuffer,".txt ");
        strcat(urlbuffer, url);
        system(urlbuffer);
        file_no++;
    }
}
void getpage(char *url)
{
    FILE *inputFile;
    inputFile=fopen("crawler_directory/temp.txt","w");
    if(inputFile==NULL)
    {
        fprintf(stderr," ERROR OPENING FILE ");
    }
    else
    {
        char urlbuffer[1000]={0};
        strcat(urlbuffer,"wget -O ");
        strcat(urlbuffer,"~/desktop/crawler_directory/temp.txt ");
        strcat(urlbuffer, url);
        system(urlbuffer);
    }
}
void mm(int argv,char *args[100],int depthvar)
{
    if(depthvar==maxdepth)
    {
        cout<<"Depth is not correct\n";
        return;
    }
    else
    {
        int i=0,k=0,j=0,c=0;
        linklist l;
        printf("\n\n\n Depth=%d \n\n\n",depthvar);
        char *ptr[maxurl];
        for(i=0;i<argv;i++)
        {
            cout<<args[i]<<"\n";
        }
        if(argv!=3)
        {
            cout<<"Arguments passed is not equal to 3\n";
        }
        if(strcmp(args[1],"seedurl")==0)
        {
            cout<<"SEED URL\n";
            return;
        }
        char linktotest[140];
        strcat(linktotest,"wget --spider ");
        strcat(linktotest,args[1]);
        if(!system(linktotest))
        {printf("\n\n\n\nInvalid URL\n\n\n\n");
        }
        else{
        }
        testDir(args[2]);
        getpage(args[1]);
        safe_keeping_page(args[1]);
        
        /* File to string */
        
        struct stat st; //variable which will count length of file.
        stat("crawler_directory/temp.txt",&st);
        int file_size=st.st_size;
        ifstream t;
        t.open("crawler_directory/temp.txt");
        t.seekg(0, std::ios::beg);
        char filechar[file_size];
        t.read(filechar, file_size);
        t.close();
        
        /* Extracting Links From String */
        char checktemp;
        for(i=0;i<file_size;i++)
        {
            if(filechar[i]=='a')
            {
                i++;
                if(filechar[i]==' ')
                {
                    i++;
                    if(filechar[i]=='h')
                    {
                        i++;
                        if(filechar[i]=='r')
                        {
                            i++;
                            if(filechar[i]=='e')
                            {
                                i++;
                                if(filechar[i]=='f')
                                {
                                    i=i+2;
                                    checktemp=filechar[i];
                                    i++;
                                    if(filechar[i]!='h'){}
                                    else{
                                        ptr[k]=(char*)malloc(maxurllength*(sizeof(char)));
                                        while(filechar[i]!=checktemp && j<maxurllength)
                                        {
                                            *(ptr[k]+j)=filechar[i];
                                            i++;
                                            j++;
                                        }
                                        *(ptr[k]+j)='\0';
                                        if(l.check(ptr[k])==0)
                                        {
                                            linktotest[0]=0;
                                            strcat(linktotest,"wget --spider ");
                                            strcat(linktotest,ptr[k]);
                                            l.inserttail(ptr[k],depthvar);
                                            j=0;k++;c++;
                                            if(c==maxurl)
                                            {
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        /* Printing urls */
        cout<<"\n\n\n"<<k<<"\n\n\n";
        for(i=0;i<k;i++)
        {
            cout<<"\n"<<ptr[i]<<"\n";
        }
        for(i=0;i<k;i++)
        {
            args[1]=ptr[i];
            mm(argv,args,depthvar+1);
        }
    }
}
int main(int argv,char *args[100])
{
    int depthvar=1;
    mm(argv,args,depthvar);
}

