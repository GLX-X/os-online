#include <stdio.h>
#include <stdlib.h>  
int main()
{
   int req[50];       
   int visited[50];  
   int n, head;
   int total_movement = 0;
   printf("Enter number of disk requests: ");
   scanf("%d", &n);
   printf("Enter disk requests:\n");
   for(int i = 0; i < n; i++)
   {
       scanf("%d", &req[i]);
       visited[i] = 0; // mark all as not visited
   }
   printf("Enter initial head position: ");
   scanf("%d", &head);
   for(int i = 0; i < n; i++)
   {
       int min = 100000;
       int index = -1;
       for(int j = 0; j < n; j++)
       {
           if(visited[j] == 0)
           {
               int distance = abs(req[j] - head);
               if(distance < min)
               {
                   min = distance;
                   index = j;
               }
           }
       }
       total_movement += min;
       head = req[index];
       visited[index] = 1;
   }
   printf("Total Head Movement (SSTF) = %d\n", total_movement);
   return 0;
}


