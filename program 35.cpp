#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100 // Maximum number of blocks in the file
#define BLOCK_SIZE 512 // Size of each block (in bytes)

// Structure to represent a block in the file
typedef struct Block {
    char data[BLOCK_SIZE];
} Block;

// Structure to represent the index block
typedef struct IndexBlock {
    int blockPointers[MAX_BLOCKS]; // Array to store block pointers
    int numOfBlocks; // Number of blocks in the file
} IndexBlock;

// Function to simulate the file allocation strategy
void simulateFileAllocation(IndexBlock *indexBlock) {
    printf("Simulating file allocation strategy...\n");

    // Reading blocks using index block pointers
    for (int i = 0; i < indexBlock->numOfBlocks; i++) {
        printf("Reading Block %d: %s\n", i + 1, indexBlock->blockPointers[i] == -1 ? "Empty" : "Data");
    }
}

int main() {
    IndexBlock indexBlock;
    indexBlock.numOfBlocks = 0;

    // Initialize block pointers to -1 (indicating empty)
    for (int i = 0; i < MAX_BLOCKS; i++) {
        indexBlock.blockPointers[i] = -1;
    }

    printf("Enter the number of blocks in the file: ");
    scanf("%d", &indexBlock.numOfBlocks);

    // Check for valid number of blocks
    if (indexBlock.numOfBlocks <= 0 || indexBlock.numOfBlocks > MAX_BLOCKS) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    // Simulate file allocation strategy
    simulateFileAllocation(&indexBlock);

    return 0;
}
