#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DISK_SIZE 1000  // Total number of blocks on the disk
#define BLOCK_SIZE 512   // Size of each block (in bytes)
#define MAX_FILES 10     // Maximum number of files in the system

// Structure to represent a file
typedef struct {
    int startBlock;     // Starting block number of the file
    int numBlocks;      // Number of blocks allocated to the file
} File;

// Structure to represent the disk
typedef struct {
    bool allocated[DISK_SIZE];  // Array to track allocated blocks on the disk
} Disk;

// Function to initialize the disk
void initializeDisk(Disk *disk) {
    for (int i = 0; i < DISK_SIZE; i++) {
        disk->allocated[i] = false;
    }
}

// Function to allocate blocks to a file
bool allocateBlocks(Disk *disk, File *file) {
    int blocksNeeded = file->numBlocks;

    // Find contiguous free blocks
    int consecutiveBlocks = 0;
    for (int i = 0; i < DISK_SIZE; i++) {
        if (!disk->allocated[i]) {
            consecutiveBlocks++;
            if (consecutiveBlocks == blocksNeeded) {
                file->startBlock = i - blocksNeeded + 1;
                break;
            }
        } else {
            consecutiveBlocks = 0;
        }
    }

    // Check if enough contiguous free blocks are found
    if (consecutiveBlocks == blocksNeeded) {
        // Mark allocated blocks on the disk
        for (int i = file->startBlock; i < file->startBlock + blocksNeeded; i++) {
            disk->allocated[i] = true;
        }
        return true;
    } else {
        printf("Error: Not enough contiguous free blocks.\n");
        return false;
    }
}

// Function to simulate file allocation
void simulateFileAllocation(Disk *disk, File files[], int numFiles) {
    printf("Simulating file allocation strategy...\n");
    for (int i = 0; i < numFiles; i++) {
        printf("File %d: Blocks [%d-%d]\n", i+1, files[i].startBlock, files[i].startBlock + files[i].numBlocks - 1);
    }
}

int main() {
    Disk disk;
    initializeDisk(&disk);

    int numFiles;
    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    if (numFiles > MAX_FILES) {
        printf("Error: Exceeded maximum number of files.\n");
        return 1;
    }

    File files[numFiles];

    for (int i = 0; i < numFiles; i++) {
        printf("Enter number of blocks for File %d: ", i+1);
        scanf("%d", &files[i].numBlocks);

        if (files[i].numBlocks <= 0 || files[i].numBlocks > DISK_SIZE) {
            printf("Error: Invalid number of blocks for File %d.\n", i+1);
            return 1;
        }

        if (!allocateBlocks(&disk, &files[i])) {
            return 1;
        }
    }

    // Simulate file allocation
    simulateFileAllocation(&disk, files, numFiles);

    return 0;
}
