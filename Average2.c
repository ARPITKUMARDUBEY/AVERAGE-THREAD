include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<fcntl.h>
#include<malloc.h>
struct node 
{
  int data;
  struct node *next;
};

struct node *start=NULL;
struct node *create(struct node *);
struct node *display(struct node *);
void *thread_average(void *start);
void *thread_maximumvalue(void *start);
void *thread_minimumvalue(void *start);

struct node *create(struct node *start)
{
   int num;
   write(1,"PLEASE ENTER THE NEGATIVE NUMBER TO EXIT \n",45);
   write(1,"PLEASE ENTER THE DATA = ",24);
   scanf("%d",&num);
   while(num>-1)
   { 
      struct node *newnode,*ptr;
      newnode=(struct node*)malloc(sizeof(struct node));
      newnode->data=num;
      if(start==NULL)
      {
          newnode->next=NULL;
          start=newnode;
      }
      else
      {
          ptr=start;
          while(ptr->next!=NULL)
          {
              ptr=ptr->next;
          }
          ptr->next=newnode;
          newnode->next=NULL;
      }
      write(1,"PLEASE ENTER THE DATA = ",24);
      scanf("%d",&num);    
   }
   printf("\n\n");  
   return start;    
}

struct node *display(struct node *start)
{
    struct node *ptr;
    ptr=start;
    while(ptr!=NULL)
    {
       printf("%d\t",ptr->data);
       ptr=ptr->next;
    } 
    printf("\n\n");
    return start;
}

int main()
{
   int res,count;
   pthread_t a_thread,a_thread2,a_thread3;
   start=create(start);
   start=display(start);
   res=pthread_create(&a_thread,NULL,thread_average,start);
   res=pthread_create(&a_thread2,NULL,thread_maximumvalue,start); 

   if(res!=0)
   {
      perror("\nTHREAD CREATION FAILED OF ERROR 02.1\n");
      exit(EXIT_FAILURE);
   } 
   res=pthread_join(a_thread,NULL);
   res=pthread_join(a_thread2,NULL);


   return 0;
}

void *thread_average(void *start)
{
    struct node *ptr;
    int average=0,count=0,sum=0; 
    ptr=start;
    while(ptr!=NULL)
    {
       sum=sum+ptr->data;
       ptr=ptr->next;
       count++; 
    }
    average=sum/count;
    printf("AVERAGE OF THE NUMBER IS = %d ",average); 
}

void *thread_maximumvalue(void *start)
{
    struct node *ptr,*preptr;
    ptr=start;
    int count=0;
    int i=0;
    int j=0; 
    while(ptr!=NULL)
    {
       ptr=ptr->next;
       count++; 
    }
    ptr=start; 
    for(i=0;i<count;i++)
    {  
       preptr=start;
       for(j=0;j<count;j++)
       {
          if(ptr->data<=preptr->data)
          {
             int c=ptr->data;
             ptr->data=preptr->data;
             preptr->data=c;  
             preptr=preptr->next; 
          }
          else
          {
             preptr=preptr->next;
          }        
       }
       ptr=ptr->next;     
    }
    ptr=start;    
    while(ptr->next!=NULL)
    {
       ptr=ptr->next;
    }    
    printf("\nMAXIMUM VALUE OF THE NUMBER IS = %d ",ptr->data);
}
