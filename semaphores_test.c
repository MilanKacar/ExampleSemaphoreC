/*
    SEMAPHORE EXAMPLE:
    - given are 100 persons
    - 10 persons will fit the table
    - every person should sit for 1 sec. at the table
    - the execution should be as fast as posible
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 

#define NUM_PLACES 10
#define NUM_PERSONS 100

// TABLE with init values = 0 -> no one is sitting here
int table[NUM_PLACES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

pthread_t threads_tid[NUM_PERSONS];
sem_t mutex;
int value;

void *test_thread()
{   

    sem_wait(&mutex);
    int i = 0;
    // find the free place at the table
    while (table[i]!=0)
    {
        i++;
    }
    // take a sit
    table[i] = 1;
    printf("Person is using the position with an id : %d\n", i);
    //sit for 1 sec.
    sleep(1);

    //stand up
    table[i] = 0;
    sem_post(&mutex);

    return (void*) 999;
}

int main(void)
{
    sem_init(&mutex, 0, NUM_PLACES);
    printf("Num of persons : %d\n", NUM_PERSONS);
    sleep(1);
    int i = 0;
    for (; i < NUM_PERSONS; i++)
    {
        pthread_create(&threads_tid[i],NULL,test_thread, NULL); 
    }
    i = 0;
    for (; i < NUM_PERSONS; i++)
    {
        pthread_join(threads_tid[i],NULL); 
    }
    sem_destroy(&mutex); 
    return 0;
}