#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 1000

// Function to sort an array in ascending order
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to simulate C-SCAN disk scheduling algorithm
int CSCAN(int queue[], int head, int size, int direction) {
    int totalMovement = 0;
    int currentIndex = 0;
    int i;

    sort(queue, size); // Sort the request queue

    if (direction == 1) { // Moving towards higher cylinder numbers
        // Find the index where head movement should change direction
        for (i = 0; i < size; i++) {
            if (queue[i] >= head) {
                currentIndex = i;
                break;
            }
        }
    } else { // Moving towards lower cylinder numbers
        // Find the index where head movement should change direction
        for (i = size - 1; i >= 0; i--) {
            if (queue[i] <= head) {
                currentIndex = i;
                break;
            }
        }
    }

    // Calculate head movement
    for (i = currentIndex; i < size; i++) {
        totalMovement += abs(queue[i] - head);
        head = queue[i];
    }

    if (direction == 1) {
        totalMovement += abs(head - 0); // Move to cylinder 0
        head = 0;
        totalMovement += abs(head - queue[0]); // Move to the first cylinder after 0
        head = queue[0];
        for (i = 1; i < size; i++) {
            totalMovement += abs(queue[i] - head);
            head = queue[i];
        }
    } else {
        totalMovement += abs(head - 0); // Move to cylinder 0
        head = 0;
        totalMovement += abs(head - queue[size - 1]); // Move to the last cylinder before 0
        head = queue[size - 1];
        for (i = size - 2; i >= 0; i--) {
            totalMovement += abs(queue[i] - head);
            head = queue[i];
        }
    }

    return totalMovement;
}

int main() {
    int n; // Number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requestQueue[MAX_REQUESTS]; // Disk request queue

    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requestQueue[i]);
    }

    int initialHead; // Initial position of the head
    printf("Enter the initial position of the head: ");
    scanf("%d", &initialHead);

    int direction; // Direction of head movement (1: towards higher cylinder numbers, 0: towards lower cylinder numbers)
    printf("Enter the direction of head movement (1 for towards higher cylinder numbers, 0 for towards lower cylinder numbers): ");
    scanf("%d", &direction);

    int totalHeadMovement = CSCAN(requestQueue, initialHead, n, direction);

    printf("Total head movement: %d\n", totalHeadMovement);

    return 0;
}

