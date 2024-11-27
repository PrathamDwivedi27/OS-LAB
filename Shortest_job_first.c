#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the process structure
struct process {
    int burst, wait, no; // Burst time, waiting time, and process number
} p[20] = {0, 0};

int main() {
    int n, i, j, totalwait = 0, totalturn = 0;

    // Input the number of processes
    printf("\nEnter The Number Of Processes: ");
    scanf("%d", &n);

    // Seed random number generator
    srand(time(0));

    // Generate random burst times for each process
    for (i = 0; i < n; i++) {
        p[i].burst = (rand() % 10) + 1; // Random burst time between 1 and 10 ms
        p[i].no = i + 1;               // Assign process number
        printf("Burst Time (in ms) For Process #%2d: %d\n", p[i].no, p[i].burst);
    }

    // Sort processes by burst time using Bubble Sort
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].burst > p[j + 1].burst) {
                // Swap burst times
                p[j].burst ^= p[j + 1].burst;
                p[j + 1].burst ^= p[j].burst;
                p[j].burst ^= p[j + 1].burst;

                // Swap process numbers
                p[j].no ^= p[j + 1].no;
                p[j + 1].no ^= p[j].no;
                p[j].no ^= p[j + 1].no;
            }
        }
    }

    // Print the header for the output
    printf("\nProcess \t Waiting Time  TurnAround Time ");
    printf("\n--------------------------------------------");

    // Calculate waiting and turnaround times
    for (i = 0; i < n; i++) {
        printf("\nProcess # %-12d%-15d%-15d", p[i].no, p[i].wait, p[i].wait + p[i].burst);
        p[i + 1].wait = p[i].wait + p[i].burst; // Waiting time for the next process
        totalwait += p[i].wait;
        totalturn += p[i].wait + p[i].burst;
    }

    // Print averages
    printf("\n\nAverage\n---------");
    printf("\nWaiting Time     : %.2f ms", totalwait / (float)n);
    printf("\nTurnAround Time  : %.2f ms\n\n", totalturn / (float)n);

    return 0;
}
