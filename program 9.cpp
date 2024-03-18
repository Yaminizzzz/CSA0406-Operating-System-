#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key;
    char *shm;

    // Generate a unique key for the shared memory segment
    key = ftok("shmfile", 'R');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to our data space
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Parent process (producer) writes a message to shared memory
    sprintf(shm, "Hello, shared memory!");

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process (consumer) reads from shared memory
        printf("Child process (consumer) reads from shared memory: %s\n", shm);
        // Detach from the shared memory segment
        if (shmdt(shm) == -1) {
            perror("shmdt");
            exit(1);
        }
    } else {
        // Parent process (producer) waits for the child to finish
        wait(NULL);
        // Detach from the shared memory segment
        if (shmdt(shm) == -1) {
            perror("shmdt");
            exit(1);
        }
        // Mark the shared memory segment for deletion
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    }

    return 0;
}
