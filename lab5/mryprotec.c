#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAGES 50
#define PAGE_SIZE 4096 // 4KB

typedef struct {
    int frameNumber;
    int valid;
    int canRead;
    int canWrite;
    int canExecute;
} PageTableEntry;

PageTableEntry pageTable[MAX_PAGES];
int numPages;

void addPage(int pageNo, int frameNo, char *perms) {
    pageTable[pageNo].frameNumber = frameNo;
    pageTable[pageNo].valid = 1;
    pageTable[pageNo].canRead = strchr(perms, 'R') != NULL;
    pageTable[pageNo].canWrite = strchr(perms, 'W') != NULL;
    pageTable[pageNo].canExecute = strchr(perms, 'X') != NULL;
}

void accessMemory(char *op, int logicalAddr) {
    int pageNo = logicalAddr / PAGE_SIZE;
    int offset = logicalAddr % PAGE_SIZE;

    if (pageNo >= numPages || !pageTable[pageNo].valid) {
        printf("%s at 0x%X -> VIOLATION: INVALID PAGE\n", op, logicalAddr);
        return;
    }

    PageTableEntry pte = pageTable[pageNo];
    int allowed = 0;

    if (strcmp(op, "READ") == 0) allowed = pte.canRead;
    else if (strcmp(op, "WRITE") == 0) allowed = pte.canWrite;
    else if (strcmp(op, "EXECUTE") == 0) allowed = pte.canExecute;

    if (!allowed) {
        printf("%s at 0x%X -> VIOLATION: PROTECTION FAULT\n", op, logicalAddr);
    } else {
        int physAddr = pte.frameNumber * PAGE_SIZE + offset;
        printf("%s at 0x%X -> Physical Address 0x%X\n", op, logicalAddr, physAddr);
    }
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    fscanf(fp, "%d", &numPages);

    for (int i = 0; i < numPages; i++) {
        int frame;
        char perms[4];
        fscanf(fp, "%d %s", &frame, perms);
        addPage(i, frame, perms);
    }

    int numReq;
    fscanf(fp, "%d", &numReq);

    for (int i = 0; i < numReq; i++) {
        char op[10];
        int addr;
        fscanf(fp, "%s %x", op, &addr);
        accessMemory(op, addr);
    }

    fclose(fp);
    return 0;
}
