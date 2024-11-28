#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[1000], sourceFile[256], destFile[256];
    int sourceFD, destFD, bytesRead;

    // Get source and destination file names
    printf("Enter source filename: ");
    scanf("%s", sourceFile);
    printf("Enter destination filename: ");
    scanf("%s", destFile);

    // Open the source file in read-only mode
    sourceFD = open(sourceFile, O_RDONLY);
    if (sourceFD < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Open or create the destination file in write-only mode
    destFD = open(destFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (destFD < 0) {
        perror("Error opening destination file");
        close(sourceFD);
        return 1;
    }

    // Read from source and write to destination
    while ((bytesRead = read(sourceFD, buffer, sizeof(buffer))) > 0) {
        if (write(destFD, buffer, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFD);
            close(destFD);
            return 1;
        }
    }

    if (bytesRead < 0) {
        perror("Error reading from source file");
    }

    // Close the file descriptors
    close(sourceFD);
    close(destFD);

    printf("File copy operation completed successfully.\n");
    return 0;
}
