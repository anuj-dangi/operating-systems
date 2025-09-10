#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct {
    int size;
    int allocated;   // 1 if allocated, 0 if free
} Block;

typedef struct {
    int size;
    int allocated;   // 1 if allocated, 0 if not
    int blockIndex;  // which block is allocated
} Process;

void resetAllocations(Process proc[], int pn, Block blk[], int bn) {
    for (int i = 0; i < pn; i++) {
        proc[i].allocated = 0;
        proc[i].blockIndex = -1;
    }
    for (int i = 0; i < bn; i++) {
        blk[i].allocated = 0;
    }
}

void firstFit(Process proc[], int pn, Block blk[], int bn) {
    resetAllocations(proc, pn, blk, bn);
    for (int i = 0; i < pn; i++) {
        for (int j = 0; j < bn; j++) {
            if (!blk[j].allocated && blk[j].size >= proc[i].size) {
                proc[i].allocated = 1;
                proc[i].blockIndex = j;
                blk[j].allocated = 1;
                break;
            }
        }
    }
}

void nextFit(Process proc[], int pn, Block blk[], int bn) {
    resetAllocations(proc, pn, blk, bn);
    int lastPos = 0;
    for (int i = 0; i < pn; i++) {
        int j = lastPos, count = 0;
        while (count < bn) {
            if (!blk[j].allocated && blk[j].size >= proc[i].size) {
                proc[i].allocated = 1;
                proc[i].blockIndex = j;
                blk[j].allocated = 1;
                lastPos = (j + 1) % bn;
                break;
            }
            j = (j + 1) % bn;
            count++;
        }
    }
}

void bestFit(Process proc[], int pn, Block blk[], int bn) {
    resetAllocations(proc, pn, blk, bn);
    for (int i = 0; i < pn; i++) {
        int bestIdx = -1;
        for (int j = 0; j < bn; j++) {
            if (!blk[j].allocated && blk[j].size >= proc[i].size) {
                if (bestIdx == -1 || blk[j].size < blk[bestIdx].size) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            proc[i].allocated = 1;
            proc[i].blockIndex = bestIdx;
            blk[bestIdx].allocated = 1;
        }
    }
}

void worstFit(Process proc[], int pn, Block blk[], int bn) {
    resetAllocations(proc, pn, blk, bn);
    for (int i = 0; i < pn; i++) {
        int worstIdx = -1;
        for (int j = 0; j < bn; j++) {
            if (!blk[j].allocated && blk[j].size >= proc[i].size) {
                if (worstIdx == -1 || blk[j].size > blk[worstIdx].size) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            proc[i].allocated = 1;
            proc[i].blockIndex = worstIdx;
            blk[worstIdx].allocated = 1;
        }
    }
}

void calculateFragmentation(Process proc[], int pn, Block blk[], int bn) {
    int internal = 0, external = 0;
    for (int i = 0; i < pn; i++) {
        if (proc[i].allocated) {
            int blkSize = blk[proc[i].blockIndex].size;
            internal += (blkSize - proc[i].size);
        }
    }
    for (int i = 0; i < bn; i++) {
        if (!blk[i].allocated) {
            external += blk[i].size;
        }
    }
    printf("\nInternal Fragmentation: %d", internal);
    printf("\nExternal Fragmentation: %d\n", external);
}

void display(Process proc[], int pn) {
    printf("\nProcess Allocation:\n");
    for (int i = 0; i < pn; i++) {
        if (proc[i].allocated)
            printf("Process %d (size %d) -> Block %d\n", i+1, proc[i].size, proc[i].blockIndex+1);
        else
            printf("Process %d (size %d) -> Not Allocated\n", i+1, proc[i].size);
    }
}

int main() {
    int bn, pn, choice;
    Block blk[MAX];
    Process proc[MAX];

    printf("Enter number of blocks: ");
    scanf("%d", &bn);
    for (int i = 0; i < bn; i++) {
        printf("Enter size of block %d: ", i+1);
        scanf("%d", &blk[i].size);
        blk[i].allocated = 0;
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &pn);
    for (int i = 0; i < pn; i++) {
        printf("Enter size of process %d: ", i+1);
        scanf("%d", &proc[i].size);
        proc[i].allocated = 0;
        proc[i].blockIndex = -1;
    }

    do {
        printf("\nMemory Management Algorithms\n");
        printf("1. First Fit\n2. Next Fit\n3. Best Fit\n4. Worst Fit\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: firstFit(proc, pn, blk, bn);
                    display(proc, pn);
                    calculateFragmentation(proc, pn, blk, bn);
                    break;
            case 2: nextFit(proc, pn, blk, bn);
                    display(proc, pn);
                    calculateFragmentation(proc, pn, blk, bn);
                    break;
            case 3: bestFit(proc, pn, blk, bn);
                    display(proc, pn);
                    calculateFragmentation(proc, pn, blk, bn);
                    break;
            case 4: worstFit(proc, pn, blk, bn);
                    display(proc, pn);
                    calculateFragmentation(proc, pn, blk, bn);
                    break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    } while(1);

    return 0;
}
