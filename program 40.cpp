#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char *filename = "testfile.txt";
    char *content = "Hello, world!\n";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; // Permissions: rw-rw-r--

    // Create the file
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
    if (fd == -1) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }

    // Write content to the file
    if (write(fd, content, strlen(content)) == -1) {
        perror("Failed to write to file");
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fd) == -1) {
        perror("Failed to close file");
        exit(EXIT_FAILURE);
    }

    // Simulate different users attempting to access the file
    printf("Simulating different users accessing the file:\n");

    // Owner
    printf("Owner:\n");
    if (access(filename, R_OK | W_OK) == 0) {
        printf("  Read and write access granted\n");
    } else {
        printf("  Read and write access denied\n");
    }

    // Group
    printf("Group:\n");
    if (access(filename, R_OK | W_OK) == 0) {
        printf("  Read and write access granted\n");
    } else {
        printf("  Read and write access denied\n");
    }

    // Others
    printf("Others:\n");
    if (access(filename, R_OK) == 0) {
        printf("  Read access granted\n");
    } else {
        printf("  Read access denied\n");
    }

    return 0;
}
