#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (id + 1) % NUM_PHILOSOPHERS
#define EATING_TIME 2
#define THINKING_TIME 1

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(THINKING_TIME);

        printf("Philosopher %d is hungry\n", id);
        pthread_mutex_lock(&forks[LEFT]);
        pthread_mutex_lock(&forks[id]);

        printf("Philosopher %d is eating\n", id);
        sleep(EATING_TIME);

        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[LEFT]);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, philosopher, &ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
