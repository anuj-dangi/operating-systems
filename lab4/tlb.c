#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 10
#define MAX_TLB_SIZE 256

typedef struct {
    int pid;
    int page;
} TLBEntry;

typedef struct {
    TLBEntry entries[MAX_TLB_SIZE];
    int size;
    int capacity;
} TLB;

void tlbAccess(TLB *tlb, int pid, int page, int *hit) {
    *hit = 0;
    for (int i = 0; i < tlb->size; i++) {
        if (tlb->entries[i].pid == pid && tlb->entries[i].page == page) {
            *hit = 1;
            TLBEntry temp = tlb->entries[i];
            for (int j = i; j < tlb->size - 1; j++) {
                tlb->entries[j] = tlb->entries[j + 1];
            }
            tlb->entries[tlb->size - 1] = temp;
            return;
        }
    }
    if (tlb->size < tlb->capacity) {
        tlb->entries[tlb->size].pid = pid;
        tlb->entries[tlb->size].page = page;
        tlb->size++;
    } else {
        for (int i = 0; i < tlb->size - 1; i++) {
            tlb->entries[i] = tlb->entries[i + 1];
        }
        tlb->entries[tlb->size - 1].pid = pid;
        tlb->entries[tlb->size - 1].page = page;
    }
}

int main() {
    int n = 3;
    int Mi[MAX_PROCESSES] = {4096, 8192, 2048};
    double h = 0.8;
    double T = 100.0;
    double t = 10.0;
    int tlb_size = 128;
    int accesses = 10000;

    srand(time(NULL));
    TLB tlb = {.size = 0, .capacity = tlb_size};

    long total_refs = 0, hits = 0, misses = 0;
    double total_time = 0.0;

    for (int pid = 0; pid < n; pid++) {
        for (int i = 0; i < accesses; i++) {
            total_refs++;
            int page;
            if ((double)rand() / RAND_MAX < h) {
                int hot_limit = (Mi[pid] / 100) > 0 ? (Mi[pid] / 100) : 1;
                page = rand() % hot_limit;
            } else {
                page = rand() % Mi[pid];
            }
            int hit;
            tlbAccess(&tlb, pid, page, &hit);
            if (hit) {
                hits++;
                total_time += (t + T);
            } else {
                misses++;
                total_time += (t + 2 * T);
            }
        }
    }

    double observed_h = (double)hits / total_refs;
    double experimental_eat = total_time / total_refs;
    double theoretical_eat = t + (2 - h) * T;

    printf("=== TLB Simulation ===\n");
    printf("Total refs: %ld\n", total_refs);
    printf("Hits: %ld  Misses: %ld\n", hits, misses);
    printf("Observed hit ratio: %.4f\n", observed_h);
    printf("Experimental EAT: %.4f ns\n", experimental_eat);
    printf("Theoretical EAT (from input h=%.2f): %.4f ns\n", h, theoretical_eat);

    return 0;
}
