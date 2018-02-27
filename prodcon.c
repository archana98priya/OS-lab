#include<stdio.h>
#include<string.h>

// pthread support library
#include<pthread.h>
// semaphore support library
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>

// buffer size count
#define N 5


// buffer
int buffer[N];

int in = 0, out = 0;


// semaphores for producers consumers problem
sem_t mutex, full, empty;


/**
 *  initialize semaphore varilables
 */
void initSemaphores() {

    // sem_init(semaphore variable reference, 0 to share semaphore between all threads, inital value)

    // mutex (mutual exclusion) variable
    sem_init(&mutex, 0, 1);

    // full check semaphore
    sem_init(&full, 0, 0);

    // empty check semaphore
    sem_init(&empty, 0, N);

}



/**
 *  Procuder program with semaphores
 */
void *producer() {

    // run finite length

    //int i;


       //z++;
  //  for (i = 0; i < 10; i++) {

        // check for full buffer
        // if buffer is full then put this process in sleep queue
        // else add a item by using mutex semaphore
        sem_wait(&empty);

        // check whether any other process is accessing buffer
        // if yes put this process to sleep
        // else add the element to the buffer
        sem_wait(&mutex);

        // produced item

        int z= rand() %100;
        printf("Produced item is: %d\n",z);

        // add element to the buffer
        buffer[in] = z;
        in = (in + 1) % N;
        sleep(1);

        // free the mutex semaphore and and wake up a process in the sleep queue
        sem_post(&mutex);

        // increment the full semaphore indicating the addition of new element to the buffer is complete
        sem_post(&full);

   // }

}



/**
 *  Consumer program with semaphores
 */
void *consumer() {

    int item;

    // run finite length
   // i++ ;
  //  for (i = 0; i < 10; i++) {

        // check for empty buffer
        // if buffer is empty then put this process to sleep
        // else remove a item by using mutex semaphore
        sem_wait(&full);

        // check whether any other process is accessing buffer
        // if yes put this process to sleep
        // else add the element to the buffer
        sem_wait(&mutex);

        // remove element from the buffer
        item = buffer[out];
        // consumed item
        printf("Consumed item is: %d\n", item);
        out = (out + 1) % N;
        sleep(1);

        // free the mutex semaphore and and wake up a process in the sleep queue
        sem_post(&mutex);

        // increment the empty semaphore indicating the removal of new element to the buffer is complete
        sem_post(&empty);

  //  }

}




int main() {

    initSemaphores();

    // declare pthread (POSIX threads) ids
    // A thread is a single sequence stream within in a process
    pthread_t produce[10], consume[10];

    // create threads
   int i;
    for(i=0;i<10;i++){
    pthread_create(&produce[i] ,NULL, producer, NULL);
    pthread_create(&consume[i], NULL, consumer, NULL);
    }


    for(i=0;i<10;i++)
    {
    // join thread
    pthread_join(produce[i], NULL);
    pthread_join(consume[i], NULL);
    }

    return 0;
}
