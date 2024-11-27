#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct process {
    int size;          // Size of the process
    char name[20];     // Name of the process
    int id;            // Block ID the process is allocated to
} p[20] = {0, 0};

struct block {
    int size;          // Size of the memory block
    int id;            // ID of the process allocated to the block (0 if empty)
} b[20] = {0, 0};

int main() {
    int nb, np, i, j;

    // Initialize random number generator
    srand(time(NULL));

    // Input number of blocks
    printf("\nEnter The Number Of Blocks: ");
    scanf("%d", &nb);

    // Generate random sizes for blocks
    for (i = 0; i < nb; i++) {
        b[i].size = (rand() % 201) + 50; // Random size between 50 and 250
        b[i].id = 0; // Initially, all blocks are empty
        printf("Block #%d has size: %d\n", i + 1, b[i].size);
    }

    // Input number of processes
    printf("\nEnter The Number Of Processes: ");
    scanf("%d", &np);

    // Generate random sizes for processes
    for (i = 0; i < np; i++) {
        printf("Enter The Name of Process %d: ", i + 1);
        scanf("%s", p[i].name);
        p[i].size = (rand() % 201) + 30; // Random size between 30 and 230
        p[i].id = -1; // Initially, no process is allocated to a block
        printf("Process %s has size: %d\n", p[i].name, p[i].size);
    }

    // First Fit Algorithm: Try to allocate each process to the first suitable block
    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (b[j].id == 0 && p[i].size <= b[j].size) { // Block is empty and large enough
                b[j].id = i + 1; // Allocate process to block
                p[i].id = j + 1; // Set block ID in process
                break; // Move to the next process
            }
        }
    }

    // Display Block Information
    printf("\nBlock Information\n------------------");
    printf("\nBlock ID   Block Size   Process Name   Process Size");
    for (i = 0; i < nb; i++) {
        if (b[i].id) {
            printf("\nBlock #%d     %-10d     %-10s     %-10d", 
                   i + 1, b[i].size, p[b[i].id - 1].name, p[b[i].id - 1].size);
        } else {
            printf("\nBlock #%d     %-10d     Empty         Empty", 
                   i + 1, b[i].size);
        }
    }

    // Display Process Information
    printf("\n\nProcess Information\n---------------------");
    printf("\nProcess Name   Process Size   Block ID   Block Size");
    for (i = 0; i < np; i++) {
        if (p[i].id != -1) {
            printf("\n%-10s      %-10d     %-10d   %-10d", 
                   p[i].name, p[i].size, p[i].id, b[p[i].id - 1].size);
        } else {
            printf("\n%-10s      %-10d     Waiting      Waiting", 
                   p[i].name, p[i].size);
        }
    }

    return 0;
}
