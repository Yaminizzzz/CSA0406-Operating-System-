#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "C:\\Users\\chait\\OneDrive\\Documents\\Day 4\\Q32";
    char buffer[100];

    // Create a file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    printf("File created successfully.\n");

    // Write to the file
    fprintf(file, "Hello, world!\n");
    printf("Data written to file.\n");

    // Close the file
    fclose(file);
    printf("File closed.\n");

    // Open the file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    printf("File opened for reading.\n");

    // Read from the file
    fgets(buffer, sizeof(buffer), file);
    printf("Data read from file: %s\n", buffer);

    // Close the file
    fclose(file);
    printf("File closed.\n");

    return 0;
}

