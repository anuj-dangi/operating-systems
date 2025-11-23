#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

int count = 0;

sem_t sem;

void* counter(void* args)
{
    for(int i=0;i<100;i++)
    {
        sem_wait(&sem);
        count++;
        cout << "thread: " << pthread_self() << " counter : " << count << endl;
        sem_post(&sem);
    }
    return;
}

int main()
{
    pthread_t a, b;
    
    sem_init(&sem, 0, 1);
    
    pthread_create(&a, NULL, count, NULL);
    pthread_create(&b, NULL, count, NULL);
    
    pthread_join(&a, NULL);
    pthread_join(&b, NULL);
    
    sem_destroy(&sem);
    
    return 0;
}