#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct process {
    int burst, wait;
} p[20] = {0, 0};

int main() {
    int n, i, totalwait = 0, totalturn = 0;
    
    printf("\nEnter the Number of Processes: ");
    scanf("%d", &n);

    srand(time(0));

    // Generate random burst times for each process
    for (i = 0; i < n; i++) {
        p[i].burst = (rand() % 10) + 1; // Random burst time between 1 and 10 ms
        printf("Burst Time (in ms) for Process #%2d: %d\n", i + 1, p[i].burst);
    }

    printf("\nProcess \t Waiting Time (in ms) \t TurnAround Time (in ms)\n");
    printf("---------------------------------------------------------\n");

    // Calculate waiting and turnaround times
    for (i = 0; i < n; i++) {
        printf("Process #%-10d %-20d %-20d\n", i + 1, p[i].wait, p[i].wait + p[i].burst);
        p[i + 1].wait = p[i].wait + p[i].burst; // Waiting time for the next process
        totalwait += p[i].wait;
        totalturn += p[i].wait + p[i].burst;
    }

    // Print averages
    printf("\nAVERAGE\n---------\n");
    printf("Waiting Time     : %.2f ms\n", totalwait / (float)n);
    printf("TurnAround Time  : %.2f ms\n", totalturn / (float)n);

    return 0;
}
