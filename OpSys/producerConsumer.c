#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //for threads
#include <semaphore.h> //for semaphores
#include <unistd.h> //for sleep()

#define BUFFER_SIZE 3 //so only 2 items can be on the table (2 is n - 1)
#define TIMES_THRU 10 //would loop forever, this is for example purposes

//Shared Memory:
int buffer[BUFFER_SIZE];
int in = 0; //where in buffer the producer produces an item
int out = 0; //where in buffer the consumer consumes an item

sem_t empty, full;
pthread_mutex_t mutex; //for mutual exclusion

void* producer(void* args) {
    int nextProduced = 0; //producer will produce increasing integers

    int i;
    for (i = 0; i < TIMES_THRU; ++i) {
        ++nextProduced; //increases number so new number is produced (for example purposes)
        sem_wait(&empty); //decrements semaphore
        pthread_mutex_lock(&mutex); //mutex lock only contains portion of code with shared memory

        while(((in + 1) % BUFFER_SIZE) == out); //do nothing
        buffer[in] = nextProduced; //places the produced item into the buffer/table
        printf("Produced %d\n", nextProduced); //prints what is produced
        in = (in + 1) % BUFFER_SIZE; //increases in and loops to start of buffer when the end is reached

        pthread_mutex_unlock(&mutex); //unlocks mutex lock
        sem_post(&full); //increments semaphore
        sleep(2); //wait 2ms
    }
    pthread_exit(NULL); //terminates thread so it can be joined
}

void* consumer(void* args) {
    int nextConsumed = 0;

    int i;
    for (i = 0; i < TIMES_THRU; ++i) {
        sleep(1); //wait 1ms
        sem_wait(&full); //decrements semaphore
        pthread_mutex_lock(&mutex); //mutex lock only contains portion of code with shared memory

        while(in == out); //do nothing
        nextConsumed = buffer[out]; //consumes item from buffer
        printf("Consumed %d\n", nextConsumed);
        out = (out + 1) % BUFFER_SIZE; //increases out and loops to start of buffer when the end is reached

        pthread_mutex_unlock(&mutex); //unlocks mutex lock
        sem_post(&empty); //increments semaphore
        --nextConsumed; //decreases number corresponding to next item consumed
    }
    pthread_exit(NULL); //terminates thread so it can be joined
}

int main() {
    pthread_t pThread, cThread; //declaring the producer and consumer threads
    sem_init(&empty, 0, BUFFER_SIZE); //initialize the "empty" semaphore
    sem_init(&full, 0, 0); //initialize the "full" semaphore
    pthread_mutex_init(&mutex, NULL); //initialize the mutual exclusion thread

    pthread_create(&pThread, NULL, producer, NULL); //creates new producer thread
    pthread_create(&cThread, NULL, consumer, NULL); //creates new consumer thread

    pthread_join(pThread, NULL); //waits for producer thread to terminate and detaches it
    pthread_join(cThread, NULL); //waits for consumer thread to terminate and detaches it

    //Object destruction:
    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}
