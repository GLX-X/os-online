#include <stdio.h>
#define N 5
#define M 3
void detect_deadlock(int allocation[N][M],
                     int request[N][M],
                     int available[M],
                     const char *caseName)
{
    int work[M];       
    int finish[N];   
    int found;         
    for (int i = 0; i < M; i++)
        work[i] = available[i];
    for (int i = 0; i < N; i++)
        finish[i] = 0;
    printf("\n--- %s ---\n", caseName);
    printf("Initial Work = (%d,%d,%d)\n",
           work[0], work[1], work[2]);
    do 
    {
        found = 0;   
        for (int i = 0; i < N; i++)
        {
            if (!finish[i]) 
            {
                int j;
                for (j = 0; j < M; j++) 
                {
                    if (request[i][j] > work[j])
                        break;  
                }
                if (j == M)
                {
                    for (int k = 0; k < M; k++)
                        work[k] += allocation[i][k];
                    finish[i] = 1;   
                    found = 1;      
                    printf("T%d finishes → Work = (%d,%d,%d)\n",
                           i, work[0], work[1], work[2]);
                }
            }
        }
    } while (found);  

    int deadlock = 0;
    for (int i = 0; i < N; i++)
    {
        if (!finish[i]) 
        {
            deadlock = 1;
            break;
        }
    }
    if (!deadlock)
    {
        printf("✔ System is NOT deadlocked\n");
    } 
    else 
    {
        printf("❌ System is DEADLOCKED\nDeadlocked threads: ");
        for (int i = 0; i < N; i++)
            if (!finish[i])
                printf("T%d ", i);
        printf("\n");
    }
}

int main() 
{
    int allocation[N][M] = 
    {
        {0,1,0},   
        {2,0,0},   
        {3,0,3},   
        {2,1,1},   
        {0,0,2}    
    };
    int request1[N][M] =
    {
        {0,0,0},   
        {2,0,2},   
        {0,0,0},   
        {1,0,0},   
        {0,0,2}    
    };
    int available[M] = {0,0,0};
    detect_deadlock(allocation, request1, available,
                    "CASE 1: NO DEADLOCK");

    int request2[N][M] = 
    {
        {0,0,0},   
        {2,0,2},   
        {0,0,1},   
        {1,0,0},   
        {0,0,2}    
    };
    detect_deadlock(allocation, request2, available,
                    "CASE 2: DEADLOCK");

    return 0; 
}

