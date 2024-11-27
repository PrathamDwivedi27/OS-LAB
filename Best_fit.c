
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int size; // Size required by the process
    int id;   // Block ID allocated (-1 if not allocated)
};

struct Block {
    int no;   // Block ID
    int size; // Size of the block
    int id;   // Process ID allocated (0 if not allocated)
};

int main() {
    int nb, np, i, j;

    // Seed for random number generation
    srand(time(0));

    // Randomly generate the number of blocks and processes
    nb = rand() % 10 + 5; // Random number of blocks (between 5 and 15)
    np = rand() % 10 + 3; // Random number of processes (between 3 and 12)

    struct Block b[20];
    struct Process p[20];

    printf("Generated Memory Blocks:\n");
    for (i = 0; i < nb; i++) {
        b[i].no = i + 1;             // Block ID
        b[i].size = rand() % 100 + 10; // Random size (10 to 100)
        b[i].id = 0;                 // Initially unallocated
        printf("Block #%d: Size = %d\n", b[i].no, b[i].size);
    }

    printf("\nGenerated Processes:\n");
    for (i = 0; i < np; i++) {
        p[i].size = rand() % 100 + 10; // Random size (10 to 100)
        p[i].id = -1;                 // Initially unallocated
        printf("Process #%d: Size = %d\n", i + 1, p[i].size);
    }

    // Sort blocks in ascending order of size (Best Fit requires sorted blocks)
    for (i = 0; i < nb - 1; i++) {
        for (j = 0; j < nb - i - 1; j++) {
            if (b[j].size > b[j + 1].size) {
                // Swap sizes
                int temp_size = b[j].size;
                b[j].size = b[j + 1].size;
                b[j + 1].size = temp_size;

                // Swap IDs
                int temp_no = b[j].no;
                b[j].no = b[j + 1].no;
                b[j + 1].no = temp_no;
            }
        }
    }

    // Allocate processes using Best Fit Algorithm
    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (b[j].id == 0 && p[i].size <= b[j].size) {
                b[j].id = i + 1; // Allocate block to process
                p[i].id = b[j].no; // Assign block number to process
                break;
            }
        }
    }

    // Output results
    printf("\nMemory Blocks Allocation:\n");
    printf("--------------------------------------------------\n");
    printf("Block ID | Block Size | Process ID | Process Size\n");
    printf("--------------------------------------------------\n");
    for (i = 0; i < nb; i++) {
        if (b[i].id) {
            printf("   %-6d | %-9d | %-10d | %-12d\n", b[i].no, b[i].size, b[i].id, p[b[i].id - 1].size);
        } else {
            printf("   %-6d | %-9d | %-10s | %-12s\n", b[i].no, b[i].size, "Empty", "N/A");
        }
    }

    printf("\nProcesses Allocation:\n");
    printf("--------------------------------------------------\n");
    printf("Process ID | Process Size | Block ID | Block Size\n");
    printf("--------------------------------------------------\n");
    for (i = 0; i < np; i++) {
        if (p[i].id != -1) {
            printf("   %-9d | %-12d | %-8d | %-10d\n", i + 1, p[i].size, p[i].id, b[p[i].id - 1].size);
        } else {
            printf("   %-9d | %-12d | %-8s | %-10s\n", i + 1, p[i].size, "Waiting", "N/A");
        }
    }

    return 0;
}
