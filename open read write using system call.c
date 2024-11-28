#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[100], filename[256];
    int fileFD, bytesRead;

    // Get the file name from the user
    printf("Enter file name: ");
    scanf("%s", filename);

    // Open the file in read-only mode
    fileFD = open(filename, O_RDONLY);
    if (fileFD < 0) {
        perror("Error opening file");
        return 1;
    }

    // Read from the file and write to the standard output
    while ((bytesRead = read(fileFD, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error writing to standard output");
            close(fileFD);
            return 1;
        }
    }

    if (bytesRead < 0) {
        perror("Error reading from file");
    }

    // Close the file descriptor
    close(fileFD);

    return 0;
}
