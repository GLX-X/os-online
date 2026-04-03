#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main()
{
   int a,b,c;
   int fd[2];
   pid_t pid;
   printf("Enter values  of a,b, and c:");
   scanf("%d%d%d",&a,&b,&c);
   if(pipe(fd)==-1)
   {
      perror("pipe failed");
      exit(1);
   }
   pid=fork();
   if(pid<0)
   {
      perror("fork failed");
      exit(1);
   }
   if(pid==0)
   {
      close(fd[0]);
      int term2=4*a*c;
      write(fd[1],&term2,sizeof(term2));
      close(fd[1]);
      exit(0);
   }
   else
   {
      close(fd[1]);
      int term1=b*b;
      int term2,result;
      read(fd[0],&term2,sizeof(term2));
      close(fd[0]);
      result=term1-term2;
      printf("\nComputed expression:b^2-4ac=%d-%d=%d\n",term1,term2,result);
   }
   return 0;
}
