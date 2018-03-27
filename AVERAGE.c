#include<stdio.h>
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
   res=pthread_create(&a_thread3,NULL,thread_minimumvalue,start);
   if(res!=0)
   {
      perror("\nTHREAD CREATION FAILED OF ERROR 02.1\n");
      exit(EXIT_FAILURE);
   } 
   res=pthread_join(a_thread,NULL);
   res=pthread_join(a_thread2,NULL);
   res=pthread_join(a_thread3,NULL); 

   return 0;
}
