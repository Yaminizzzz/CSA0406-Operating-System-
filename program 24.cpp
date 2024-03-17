#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int fd; // File descriptor
    ssize_t bytes_written, bytes_read;
    char buffer[BUFFER_SIZE];
    const char *file_path = "C:/Users/ravul/Downloads/collage detiles/R.collage/operating system sem-6/os lab/DAY3/Q24/Q24.cpp"; // Use forward slashes and escape backslashes

    // Open a file (create if it doesn't exist, truncate if it does)
    fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Specify permissions manually
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    const char *data_to_write = "Hello, world!\n";
    bytes_written = write(fd, data_to_write, strlen(data_to_write));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("%ld bytes written to the file.\n", bytes_written);

    // Close the file
    close(fd);

    // Open the file for reading
    fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read data from the file
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    // Null-terminate the buffer to treat it as a string
    buffer[bytes_read] = '\0';
    printf("%ld bytes read from the file: %s\n", bytes_read, buffer);

    // Close the file
    close(fd);

    return 0;
}
