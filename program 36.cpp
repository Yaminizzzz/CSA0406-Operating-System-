#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCK_SIZE 512 // Size of each block (in bytes)

// Structure to represent a block in the file
typedef struct Block {
    char data[BLOCK_SIZE];
    struct Block *next; // Pointer to the next block
} Block;

// Structure to represent a file
typedef struct File {
    Block *firstBlock; // Pointer to the first block of the file
    Block *lastBlock; // Pointer to the last block of the file
} File;

// Function to initialize a file
void initFile(File *file) {
    file->firstBlock = NULL;
    file->lastBlock = NULL;
}

// Function to add a block to the end of a file
void addBlockToFile(File *file, Block *block) {
    if (file->firstBlock == NULL) {
        // If file is empty, set the first block
        file->firstBlock = block;
    } else {
        // Link the new block to the last block
        file->lastBlock->next = block;
    }
    // Update the last block to the new block
    file->lastBlock = block;
}

// Function to simulate the file allocation strategy
void simulateFileAllocation(File *file) {
    printf("Simulating file allocation strategy...\n");

    Block *currentBlock = file->firstBlock;
    int blockCount = 0;

    // Traverse the linked list of blocks
    while (currentBlock != NULL) {
        printf("Block %d: Data\n", ++blockCount);
        currentBlock = currentBlock->next;
    }
}

// Function to free memory allocated for file blocks
void freeFile(File *file) {
    Block *currentBlock = file->firstBlock;
    Block *nextBlock;

    // Traverse the linked list of blocks and free memory
    while (currentBlock != NULL) {
        nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }

    // Reset file pointers
    file->firstBlock = NULL;
    file->lastBlock = NULL;
}

int main() {
    File file;
    initFile(&file);

    int numOfBlocks;

    printf("Enter the number of blocks in the file: ");
    scanf("%d", &numOfBlocks);

    // Create and add blocks to the file
    for (int i = 0; i < numOfBlocks; i++) {
        Block *block = (Block *)malloc(sizeof(Block));
        block->next = NULL; // Initialize next pointer to NULL
        addBlockToFile(&file, block);
    }

    // Simulate file allocation strategy
    simulateFileAllocation(&file);

    // Free memory allocated for file blocks
    freeFile(&file);

    return 0;
}
