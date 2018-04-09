#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
      int fd[2],n;
      char buffer[100];
      pid_t p;
      pipe(fd);
      p=fork();
      if(p>0)  //parent
      {
                  close(fd[0]);
                  printf("Passing value to child\n");
                  write(fd[1],"hello\n",6);
                  wait();
                 
      }
      else // child
      {
                  close(fd[1]);                
                  n=read(fd[0],buffer,100);
                  write(1,buffer,n);
      }
      return 0; 
}
