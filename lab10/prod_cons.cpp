#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t mutex, empty, full;

int buffer[5];
int in=0, out=0;

void* producer(void* args)
{
	for(int i=0; i<5; i++)
	{
		sem_wait(&empty);
		sem_wait(&mutex);

		buffer[in] = i;
		cout << "Producer produced: " << i << " at index " << in << endl;
		in = (in+1)%5;

		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}

	return NULL;
}

void* consumer(void* args)
{
	for(int i=0; i<5; i++)
	{
		sem_wait(&full);
		sem_wait(&mutex);

		int item = buffer[out];
		cout << "Consumer consumed: " << item << " from index " << out << endl;
		out = (out+1)%5;

		sem_post(&mutex);
		sem_post(&empty);
		sleep(2);
	}

	return NULL;
}

int main()
{
	pthread_t prod, cons;

	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, 5);
	sem_init(&full, 0, 0);

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;
}