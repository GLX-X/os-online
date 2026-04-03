#include <stdio.h>
#include <stdlib.h>
void sort(int arr[], int n)
{
   for(int i=0;i<n-1;i++)
   {
       for(int j=i+1;j<n;j++)
       {
           if(arr[i] > arr[j])
           {
               int temp = arr[i];
               arr[i] = arr[j];
               arr[j] = temp;
           }
       }
   }
}
int main()
{
   int req[50];
   int n, head, disk_size;
   int movement = 0;
   int pos = 0;
   printf("Enter number of disk requests: ");
   scanf("%d",&n);
   printf("Enter disk requests:\n");
   for(int i=0;i<n;i++)
       scanf("%d",&req[i]);
   printf("Enter initial head position: ");
   scanf("%d",&head);
   printf("Enter disk size: ");
   scanf("%d",&disk_size);
   sort(req,n);
   for(int i=0;i<n;i++)
   {
       if(req[i] > head)
       {
           pos = i;
           break;
       }
   }
   for(int i=pos;i<n;i++)
   {
       movement += abs(head - req[i]);
       head = req[i];
   }
   movement += abs(head - (disk_size - 1));
   head = disk_size - 1;
   movement += head;
   head = 0;
   for(int i=0;i<pos;i++)
   {
       movement += abs(head - req[i]);
       head = req[i];
   }
   printf("Total Head Movement (C-SCAN) = %d\n", movement);
   return 0;
}


