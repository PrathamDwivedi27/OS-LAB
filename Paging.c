#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 1024  // Size of each page/frame
#define NUM_PAGES 4     // Number of pages in virtual memory
#define NUM_FRAMES 2    // Number of frames in physical memory

// Page Table Entry
typedef struct {
    int frameNumber;  // Physical frame number
    int valid;        // Valid bit (1 if the page is loaded in memory, 0 otherwise)
} PageTableEntry;

void initializePageTable(PageTableEntry pageTable[], int numPages) {
    for (int i = 0; i < numPages; i++) {
        pageTable[i].frameNumber = -1;
        pageTable[i].valid = 0;
    }
}

void loadPage(int pageNumber, int physicalMemory[], int *freeFrameIndex, PageTableEntry pageTable[]) {
    if (*freeFrameIndex >= NUM_FRAMES) {
        printf("Error: Physical memory is full! Page replacement not implemented in this simulation.\n");
        return;
    }

    printf("Loading page %d into frame %d\n", pageNumber, *freeFrameIndex);

    pageTable[pageNumber].frameNumber = *freeFrameIndex;
    pageTable[pageNumber].valid = 1;

    // Simulate loading page content into physical memory
    physicalMemory[*freeFrameIndex] = pageNumber;

    (*freeFrameIndex)++;
}

void accessMemory(int virtualAddress, int physicalMemory[], PageTableEntry pageTable[]) {
    int pageNumber = virtualAddress / PAGE_SIZE;
    int offset = virtualAddress % PAGE_SIZE;

    if (pageNumber >= NUM_PAGES) {
        printf("Error: Virtual address out of bounds!\n");
        return;
    }

    if (pageTable[pageNumber].valid) {
        int physicalAddress = pageTable[pageNumber].frameNumber * PAGE_SIZE + offset;
        printf("Virtual Address %d -> Physical Address %d (Page %d in Frame %d)\n",
               virtualAddress, physicalAddress, pageNumber, pageTable[pageNumber].frameNumber);
    } else {
        printf("Page fault! Page %d not in physical memory.\n", pageNumber);
    }
}

int main() {
    PageTableEntry pageTable[NUM_PAGES];
    int physicalMemory[NUM_FRAMES];
    int freeFrameIndex = 0;

    initializePageTable(pageTable, NUM_PAGES);

    int virtualAddresses[] = {100, 2050, 1025, 500, 3100};
    int numAddresses = sizeof(virtualAddresses) / sizeof(virtualAddresses[0]);

    for (int i = 0; i < numAddresses; i++) {
        int virtualAddress = virtualAddresses[i];
        int pageNumber = virtualAddress / PAGE_SIZE;

        printf("\nAccessing virtual address: %d\n", virtualAddress);
        if (!pageTable[pageNumber].valid) {
            loadPage(pageNumber, physicalMemory, &freeFrameIndex, pageTable);
        }

        accessMemory(virtualAddress, physicalMemory, pageTable);
    }

    return 0;
}
