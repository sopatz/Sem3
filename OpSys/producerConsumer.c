#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> //for sleep()

#define BUFFER_SIZE 3 //so only 2 items can be on the table (2 is n - 1)
#define TIMES_THRU 10 //would loop forever, this is for example purposes

//Shared Memory:
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty, full;
pthread_mutex_t mutex; //for mutual exclusion

void* producer(void* args) {
    int nextProduced = 0;

    int i;
    for (i = 0; i < TIMES_THRU; ++i) {
        ++nextProduced;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex); //mutex lock only contains portion of code with shared memory

        while(((in + 1) % BUFFER_SIZE) == out); //do nothing
        buffer[in] = nextProduced;
        printf("Produced %d\n", nextProduced);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(2);
    }
    pthread_exit(NULL);
}

void* consumer(void* args) {
    int nextConsumed = 0;

    int i;
    for (i = 0; i < TIMES_THRU; ++i) {
        sleep(1);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        while(in == out); //do nothing
        nextConsumed = buffer[out];
        printf("Consumed %d\n", nextConsumed);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        --nextConsumed;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t pThread, cThread;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&pThread, NULL, producer, NULL);
    pthread_create(&cThread, NULL, consumer, NULL);

    pthread_join(pThread, NULL);
    pthread_join(cThread, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}
