#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the process structure
struct process {
    int burst, wait, no, priority; // Burst time, waiting time, process number, priority
} p[20] = {0, 0};

int main() {
    int n, i, j, totalwait = 0, totalturn = 0;

    // Input the number of processes
    printf("\nEnter The Number Of Processes: ");
    scanf("%d", &n);

    // Seed the random number generator
    srand(time(0));

    // Generate random burst time and priority for each process
    for (i = 0; i < n; i++) {
        p[i].burst = (rand() % 10) + 1;       // Burst time between 1 and 10
        p[i].priority = (rand() % 5) + 1;    // Priority between 1 and 5
        p[i].no = i + 1;                     // Assign process number
        printf("Process #%2d: Burst Time = %d ms, Priority = %d\n", p[i].no, p[i].burst, p[i].priority);
    }

    // Sort processes by priority (lower number = higher priority)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                // Swap burst times
                p[j].burst ^= p[j + 1].burst;
                p[j + 1].burst ^= p[j].burst;
                p[j].burst ^= p[j + 1].burst;

                // Swap process numbers
                p[j].no ^= p[j + 1].no;
                p[j + 1].no ^= p[j].no;
                p[j].no ^= p[j + 1].no;

                // Swap priorities
                p[j].priority ^= p[j + 1].priority;
                p[j + 1].priority ^= p[j].priority;
                p[j].priority ^= p[j + 1].priority;
            }
        }
    }

    // Print the table header
    printf("\nProcess\t   Starting Time  Ending Time  Waiting Time  TurnAround Time");
    printf("\n-----------------------------------------------------------------");

    // Calculate and display times
    for (i = 0; i < n; i++) {
        printf("\nProcess #%-8d%-15d%-12d%-14d%-15d", 
            p[i].no, 
            p[i].wait, 
            p[i].wait + p[i].burst, 
            p[i].wait, 
            p[i].wait + p[i].burst
        );
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
