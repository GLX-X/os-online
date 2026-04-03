#include <stdio.h>
#include <stdlib.h>
int main() 
{
   int n;
   printf("Enter number of requests: ");
   scanf("%d", &n);
   int req[n];
   printf("Enter disk requests:\n");
   for(int i = 0; i < n; i++)
   {
       scanf("%d", &req[i]);
   }
   int head;
   printf("Enter initial head position: ");
   scanf("%d", &head);
   for(int i=0;i<n-1;i++)
   {
       for(int j=i+1;j<n;j++)
       {
           if(req[i] > req[j])
           {
               int temp = req[i];
               req[i] = req[j];
               req[j] = temp;
           }
       }
   }


   int totalSeek = 0;
   printf("\nSeek Sequence: %d", head);
   for(int i=0;i<n;i++)
   {
       if(req[i] >= head) 
       {
           totalSeek += abs(head - req[i]);
           head = req[i];
           printf(" -> %d", head);
       }
   }
   for(int i=n-1;i>=0;i--)
   {
       if(req[i] < head) 
       {
           totalSeek += abs(head - req[i]);
           head = req[i];
           printf(" -> %d", head);
       }
   }
   printf("\nTotal Seek Time = %d\n", totalSeek);
   return 0;
}

