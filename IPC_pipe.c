#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipefd[2];  // Array to store pipe ends: pipefd[0] for read, pipefd[1] for write
    pid_t pid;
    char writeMessage[] = "Hello from Parent Process!";
    char readBuffer[100];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]);  // Close the read end of the pipe
        printf("Parent: Writing to pipe: %s\n", writeMessage);
        write(pipefd[1], writeMessage, strlen(writeMessage) + 1); // Write to pipe
        close(pipefd[1]);  // Close the write end after writing
    } else { // Child process
        close(pipefd[1]);  // Close the write end of the pipe
        read(pipefd[0], readBuffer, sizeof(readBuffer)); // Read from pipe
        printf("Child: Read from pipe: %s\n", readBuffer);
        close(pipefd[0]);  // Close the read end after reading
    }

    return 0;
}
