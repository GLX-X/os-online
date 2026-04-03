#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 5
sem_t chopstick[N];
sem_t mutex;
void* philosopher(void* num) 
{
    int id = *(int*)num;
    for(int i=0;i<2;i++)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);
        if (id % 2 == 0) 
        {
            sem_wait(&chopstick[id]);              
            sem_wait(&chopstick[(id + 1) % N]);    
        }
        else 
       {
            sem_wait(&chopstick[(id + 1) % N]);    
            sem_wait(&chopstick[id]);         
        }
        sem_wait(&mutex);
        printf("Philosopher %d is eating\n", id);
        sem_post(&mutex);
        sleep(2);
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);
        printf("Philosopher %d finished eating\n", id);
    }
}
int main()
{
    pthread_t tid[N];
    int phil[N];
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);
    for (int i = 0; i < N; i++)
    {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);
    return 0;
}

