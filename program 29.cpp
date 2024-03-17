#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

pthread_mutex_t mutex;
pthread_cond_t full, empty;

void *producer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; ++i) {
        item = rand() % 100; // Generate a random item
        pthread_mutex_lock(&mutex);
        while (((in + 1) % BUFFER_SIZE) == out) // Buffer is full
            pthread_cond_wait(&empty, &mutex);
        
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced item: %d\n", item);
        
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; ++i) {
        pthread_mutex_lock(&mutex);
        while (in == out) // Buffer is empty
            pthread_cond_wait(&full, &mutex);
        
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed item: %d\n", item);
        
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}
