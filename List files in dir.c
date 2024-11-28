#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    char dirName[256];
    DIR *dir;
    struct dirent *entry;

    // Prompt the user for a directory name
    printf("ENTER A DIRECTORY NAME: ");
    scanf("%s", dirName);

    // Attempt to open the specified directory
    dir = opendir(dirName);
    if (dir == NULL) {
        perror("Can't find directory");
        exit(EXIT_FAILURE);
    }

    // Read and print directory entries
    printf("Files in directory %s:\n", dirName);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}
