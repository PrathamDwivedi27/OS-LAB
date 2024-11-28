#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the process structure
struct process {
    int burst, wait, comp, f; // Burst time, waiting time, completed time, flag for completion
} p[20] = {{0, 0}};

int main() {
    int n, i, j, totalwait = 0, totalturn = 0, quantum, flag = 1, times= 0;

    // Input the number of processes
    printf("\nEnter The Number Of Processes: ");
    scanf("%d", &n);

    // Input quantum time
    printf("\nEnter The Quantum Time (in ms): ");
    scanf("%d", &quantum);

    // Seed the random number generator
    srand(time(0));

    // Generate random burst times for each process
    for (i = 0; i < n; i++) {
        p[i].burst = (rand() % 10) + 1; // Random burst time between 1 and 10
        p[i].comp = 0;                 // Initialize completed time to 0
        p[i].f = 1;                    // Mark process as incomplete
        printf("Process #%2d: Burst Time = %d ms\n", i + 1, p[i].burst);
    }

    // Print the execution header
    printf("\nOrder Of Execution\n");
    printf("\nProcess      Starting Time   Ending Time   Remaining Burst Time");
    printf("\n--------------------------------------------------------------");

    // Round Robin Execution
    while (flag == 1) {
        flag = 0; // Reset flag to check for completion
        for (i = 0; i < n; i++) {
            if (p[i].f == 1) { // Check if the process is incomplete
                flag = 1;      // There are still processes left to execute
                j = quantum;   // Set quantum as the default execution time

                if ((p[i].burst - p[i].comp) > quantum) {
                    p[i].comp += quantum; // Add quantum to completed time
                } else {
                    j = p[i].burst - p[i].comp; // Remaining burst time
                    p[i].comp = p[i].burst;     // Mark process as fully executed
                    p[i].f = 0;                // Mark process as completed
                    p[i].wait = times - (p[i].comp - j); // Calculate waiting time
                }

                // Print the execution details for this process
                printf("\nProcess # %-3d  %-15d %-12d %-15d", i + 1, times, times + j, p[i].burst - p[i].comp);
                times += j; // Increment the total time
            }
        }
    }

    // Print the waiting and turnaround times
    printf("\n\n------------------");
    printf("\nProcess      Waiting Time    TurnAround Time");
    for (i = 0; i < n; i++) {
        printf("\nProcess # %-12d%-15d%-15d", i + 1, p[i].wait, p[i].wait + p[i].burst);
        totalwait += p[i].wait;
        totalturn += p[i].wait + p[i].burst;
    }

    // Print the averages
    printf("\n\nAverage\n------------------");
    printf("\nWaiting Time     : %.2f ms", totalwait / (float)n);
    printf("\nTurnAround Time  : %.2f ms\n\n", totalturn / (float)n);

    return 0;
}
