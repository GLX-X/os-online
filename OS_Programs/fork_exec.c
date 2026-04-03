#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
   pid_t pid;

   fflush(stdout);  // ensures proper output order
   pid = fork();

   if(pid < 0)
   {
      perror("Fork failed");
      return 1;
   }
   else if(pid == 0)
   {
      printf("Child process running (PID:%d)\n", getpid());

      char *args[] = {"./myadder", "25", "75", NULL};
      execvp(args[0], args);

      perror("execvp failed");
      return 1;
   }
   else
   {
      printf("Parent process (PID:%d) created child (PID:%d)\n", getpid(), pid);
      wait(NULL);
      printf("Child process finished\n");
   }

   return 0;
}
