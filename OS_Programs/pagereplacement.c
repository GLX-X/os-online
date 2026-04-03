#include <stdio.h>
#define MAX 100
int fifo(int ref[], int n, int frames)
{
   int frame[MAX];
   int pointer = 0;     
   int faults = 0;
   for(int i=0;i<frames;i++)
       frame[i] = -1;
   for(int i=0;i<n;i++)
   {
       int page = ref[i];
       int found = 0;
       for(int j=0;j<frames;j++)
       {
           if(frame[j] == page)
           {
               found = 1;
               break;
           }
       }
       if(!found)
       {
           frame[pointer] = page;
           pointer = (pointer + 1) % frames;
           faults++;
       }
   }
   return faults;
}


int lru(int ref[], int n, int frames)
{
   int frame[MAX];
   int recent[MAX];   
   int faults = 0;
   for(int i=0;i<frames;i++)
   {
       frame[i] = -1;
       recent[i] = -1;
   }
   for(int i=0;i<n;i++)
   {
       int page = ref[i];
       int found = 0;
       for(int j=0;j<frames;j++)
       {
           if(frame[j] == page)
           {
               found = 1;
               recent[j] = i;  
               break;
           }
       }
       if(!found)
       {
           int lruIndex = 0;
           for(int j=1;j<frames;j++)
           {
               if(recent[j] < recent[lruIndex])
                   lruIndex = j;
           }
           frame[lruIndex] = page;
           recent[lruIndex] = i;
           faults++;
       }
   }
   return faults;
}


int optimal(int ref[], int n, int frames)
{
   int frame[MAX];
   int faults = 0;
   for(int i=0;i<frames;i++)
       frame[i] = -1;
   for(int i=0;i<n;i++)
   {
       int page = ref[i];
       int found = 0;
       for(int j=0;j<frames;j++)
       {
           if(frame[j] == page)
           {
               found = 1;
               break;
           }
       }
       if(!found)
       {
           int replaceIndex = -1;
           int farthest = -1;
           for(int j=0;j<frames;j++)
           {
               int k;
               for(k=i+1;k<n;k++)
               {
                   if(frame[j] == ref[k])
                       break;
               }
               if(k == n)
               {
                   replaceIndex = j;
                   break;
               }
               if(k > farthest)
               {
                   farthest = k;
                   replaceIndex = j;
               }
           }
           frame[replaceIndex] = page;
           faults++;
       }
   }
   return faults;
}


int main()
{
   int ref[MAX];
   int n, frames;
   printf("Enter number of page references: ");
   scanf("%d",&n);
   printf("Enter the page reference string:\n");
   for(int i=0;i<n;i++)
       scanf("%d",&ref[i]);
   printf("Enter number of frames: ");
   scanf("%d",&frames);
   printf("\nPage Reference String: ");
   for(int i=0;i<n;i++)
       printf("%d ",ref[i]);
   printf("\nFrame Size = %d\n",frames);
   printf("\n--- Page Replacement Results ---\n");
   printf("FIFO Page Faults : %d\n", fifo(ref,n,frames));
   printf("LRU  Page Faults : %d\n", lru(ref,n,frames));
   printf("OPT  Page Faults : %d\n", optimal(ref,n,frames));
   return 0;
}
