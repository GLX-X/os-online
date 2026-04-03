#include<stdio.h>
#include<limits.h>

struct Process
{
    int pid;
    int at;
    int bt;
};

void copyBT(int desc[], int src[], int n)
{
    for(int i=0;i<n;i++)
        desc[i]=src[i];
}

float FCFS(struct Process p[], int n)
{
    int ct[n], tat[n], wt[n];
    int time=0;

    for(int i=0;i<n;i++)
    {
        if(time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        ct[i] = time;
        tat[i] = ct[i] - p[i].at;
        wt[i] = tat[i] - p[i].bt;
    }

    float totalWT=0;
    for(int i=0;i<n;i++)
        totalWT += wt[i];

    return totalWT/n;
}

float SJF(struct Process p[], int n)
{
    int completed[n], ct[n], tat[n], wt[n];
    int time=0;
    float totalWT=0;

    for(int i=0;i<n;i++)
        completed[i]=0;

    int completedCount=0;

    while(completedCount < n)
    {
        int idx=-1, minBT=INT_MAX;

        for(int i=0;i<n;i++)
        {
            if(!completed[i] && p[i].at <= time && p[i].bt < minBT)
            {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if(idx == -1)
        {
            time++;
            continue;
        }

        time += p[idx].bt;
        ct[idx] = time;
        tat[idx] = ct[idx] - p[idx].at;
        wt[idx] = tat[idx] - p[idx].bt;

        completed[idx] = 1;
        completedCount++;
    }

    for(int i=0;i<n;i++)
        totalWT += wt[i];

    return totalWT/n;
}

float SRTF(struct Process p[], int n, int originalBT[])
{
    int remainingBT[n], completed[n];
    int tat[n], wt[n];
    int time=0, completedCount=0;

    copyBT(remainingBT, originalBT, n);

    for(int i=0;i<n;i++)
        completed[i]=0;

    while(completedCount < n)
    {
        int idx=-1, minBT=INT_MAX;

        for(int i=0;i<n;i++)
        {
            if(!completed[i] && p[i].at <= time &&
               remainingBT[i] < minBT && remainingBT[i] > 0)
            {
                minBT = remainingBT[i];
                idx = i;
            }
        }

        if(idx == -1)
        {
            time++;
            continue;
        }

        remainingBT[idx]--;
        time++;

        if(remainingBT[idx] == 0)
        {
            completed[idx] = 1;
            completedCount++;

            tat[idx] = time - p[idx].at;
            wt[idx] = tat[idx] - originalBT[idx];
        }
    }

    float totalWT=0;
    for(int i=0;i<n;i++)
        totalWT += wt[i];

    return totalWT/n;
}

float RR(struct Process p[], int n, int originalBT[], int quantum)
{
    int remainingBT[n], waiting[n], tat[n];
    copyBT(remainingBT, originalBT, n);

    int time=0, processesLeft=n;

    while(processesLeft > 0)
    {
        for(int i=0;i<n;i++)
        {
            if(p[i].at <= time && remainingBT[i] > 0)
            {
                int exec = (remainingBT[i] > quantum) ? quantum : remainingBT[i];

                remainingBT[i] -= exec;
                time += exec;

                if(remainingBT[i] == 0)
                {
                    processesLeft--;
                    tat[i] = time - p[i].at;
                    waiting[i] = tat[i] - originalBT[i];
                }
            }
            else if(p[i].at > time)
            {
                time++;
                i--;
            }
        }
    }

    float totalWT=0;
    for(int i=0;i<n;i++)
        totalWT += waiting[i];

    return totalWT/n;
}

int main()
{
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct Process p[n];
    int originalBT[n];

    for(int i=0;i<n;i++)
    {
        p[i].pid = i+1;

        printf("\nEnter Arrival Time of P%d: ",i+1);
        scanf("%d",&p[i].at);

        printf("Enter Burst Time of P%d: ",i+1);
        scanf("%d",&p[i].bt);

        originalBT[i] = p[i].bt;
    }

    printf("\nEnter Time Quantum for Round Robin: ");
    scanf("%d",&quantum);

    float fcfsWT = FCFS(p,n);
    float sjfWT  = SJF(p,n);
    float srtfWT = SRTF(p,n,originalBT);
    float rrWT   = RR(p,n,originalBT,quantum);

    printf("\n=========== Average Waiting Time Comparison ===========\n");
    printf("FCFS : %.2f\n",fcfsWT);
    printf("SJF  : %.2f\n",sjfWT);
    printf("SRTF : %.2f\n",srtfWT);
    printf("RR   : %.2f (Q = %d)\n",rrWT,quantum);
    printf("======================================================\n");

    return 0;
}
