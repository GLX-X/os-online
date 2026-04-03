#include<stdio.h>
#include<unistd.h>
int main()
{
   pid_t pid;
   pid=fork();
   if(pid<0)
   {
      perror("Fork failed");
      return 1;
   }
   else if(pid==0)
   {
      printf("I am the CHILD process!\n");
      printf("Child PID:%d\n",getpid());
      printf("parent PID(of child):%d\n",getppid());
      sleep(10);
   }
   else
   {
      printf("I am the PARENT process!\n");
      printf("Parent PID:%d\n",getpid());
      printf("Child PID(created):%d\n",pid);
      sleep(10);
   }
   return 0;
}
