#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
       int sizeofdata;
       int fd[2]; 
       pipe(fd);
       char content[10000],message[1000];
       write(1,"PLEASE ENTER THE STRING/NAME/DATA = ",36);
       sizeofdata=read(0,content,1000);
       write(1,"YOUR DATA IN PROCESS - I \n",25);
       printf("\n\n"); 
       write(1,content,sizeofdata);
       
       pid_t process_id;
       process_id=fork();
       if(process_id>0)
       {
             close(fd[0]);
             sizeofdata=read(0,content,1000);
            
             write(fd[1],message,1000);
            
       }
       else
       {
              char message[10000];
             int length,i;
             printf("\n\n");
             strcpy(message,content);
             length=strlen(message);
             for(i=0;i<length;i++)
             {
                  int convert_string_to_asciii,convert_asciii_to_string;
                  convert_string_to_asciii=message[i]; 
                  if((convert_string_to_asciii>=65)&&(convert_string_to_asciii<=93))
                  {
                       convert_asciii_to_string=convert_string_to_asciii+32;
                       message[i]=convert_asciii_to_string; 
                  } 
                  else if((convert_string_to_asciii>=97)&&(convert_string_to_asciii<=123))
                  {
                       convert_asciii_to_string=convert_string_to_asciii-32;
                       message[i]=convert_asciii_to_string; 
                  }
 
             }
             write(1,message,sizeofdata);             
       }
        
       return 0;
}

