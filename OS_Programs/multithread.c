#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

#define MAX_SIZE 100

int numbers[MAX_SIZE];
int count;
double mean, median, stddev;

void *calc_mean(void *param);
void *calc_median(void *param);
void *calc_stddev(void *param);

int compare(const void *a,const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <list of integers>\n", argv[0]);
        return 1;
    }

    count = argc - 1;

    for(int i = 0; i < count; i++)
        numbers[i] = atoi(argv[i+1]);

    pthread_t tid1, tid2, tid3;

    // Create mean thread first
    pthread_create(&tid1, NULL, calc_mean, NULL);
    pthread_join(tid1, NULL);  // Ensure mean is ready

    // Now create median and stddev threads
    pthread_create(&tid2, NULL, calc_median, NULL);
    pthread_create(&tid3, NULL, calc_stddev, NULL);

    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    printf("\nResults:\n");
    printf("Mean               = %.2f\n", mean);
    printf("Median             = %.2f\n", median);
    printf("Standard Deviation = %.2f\n", stddev);

    return 0;
}

void *calc_mean(void *param)
{
    double sum = 0.0;
    for(int i = 0; i < count; i++)
        sum += numbers[i];

    mean = sum / count;
    pthread_exit(0);
}

void *calc_median(void *param)
{
    qsort(numbers, count, sizeof(int), compare);

    if(count % 2 == 0)
        median = (numbers[count/2 - 1] + numbers[count/2]) / 2.0;
    else
        median = numbers[count/2];

    pthread_exit(0);
}

void *calc_stddev(void *param)
{
    double sum = 0.0;

    for(int i = 0; i < count; i++)
        sum += pow(numbers[i] - mean, 2);

    stddev = sqrt(sum / count);
    pthread_exit(0);
}
