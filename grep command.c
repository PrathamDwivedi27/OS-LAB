#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char filename[256], pattern[256], line[1000];
    FILE *file;

    // Get the file name from the user
    printf("Enter the file name: ");
    scanf("%s", filename);

    // Get the pattern to be searched
    printf("Enter the pattern to search for: ");
    scanf("%s", pattern);

    // Open the file in read mode
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("\nLines containing the pattern '%s':\n", pattern);

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Check if the pattern exists in the current line
        if (strstr(line, pattern)) {
            printf("%s", line);
        }
    }

    // Close the file
    fclose(file);

    return 0;
}
