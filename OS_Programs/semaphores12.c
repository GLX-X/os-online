#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t writelock;
sem_t lock;
int read_count=0;
void *reader(void *arg)
{
	int id=*(int *)arg;
	sem_wait(&lock);
	read_count++;
	if(read_count==1)
	   sem_wait(&writelock);
	sem_post(&lock);
	printf("Reader%d is READING\n",id);
	sleep(1);
	printf("Reader%d is DONE reading\n",id);
	sem_wait(&lock);
	read_count--;
	if(read_count==0)
	    sem_post(&writelock);
	 sem_post(&lock);
	return NULL;
}
void *writer(void *arg)
{
	int id=*(int *)arg;
	sem_wait(&writelock);
	printf("\tWriter %d is WRITING\n",id);
	sleep(2);
	printf("\tWriter %d id DONE writing\n",id);
	sem_post(&writelock);
	return NULL;
}
int main()
{
	pthread_t r[5],w[5];
	int ids[5];
	sem_init(&writelock,0,1);
	sem_init(&lock,0,1);
	for(int i=0;i<5;i++)
	   ids[i]=i+1;
	for(int i=0;i<5;i++)
	{
		pthread_create(&r[i],NULL,reader,&ids[i]);
		pthread_create(&w[i],NULL,writer,&ids[i]);
	}
	for(int i=0;i<5;i++)
	{
		pthread_join(r[i],NULL);
		pthread_join(w[i],NULL);
	}
	sem_destroy(&writelock);
	sem_destroy(&lock);
	return 0;
}
