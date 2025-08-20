#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_PROCESSES 1024

typedef struct {
    int pid;
    char state;
    unsigned long utime;
    unsigned long stime;
    unsigned long vsize;
} ProcessInfo;

int main() {
    DIR *proc = opendir("/proc");
    struct dirent *entry;
    ProcessInfo processes[MAX_PROCESSES];
    int count = 0;

    if (!proc) {
        perror("opendir /proc");
        return 1;
    }

    while ((entry = readdir(proc)) != NULL && count < MAX_PROCESSES) {
        if (entry->d_type == DT_DIR) {
            int pid = atoi(entry->d_name);
            if (pid > 0) {
                char stat_path[256];
                snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
                FILE *stat = fopen(stat_path, "r");
                if (stat) {
                    ProcessInfo p;
                    p.pid = pid;
                    fscanf(stat, "%*d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu %*d %*d %*d %*d %*d %*u %*u %lu",
                        &p.state, &p.utime, &p.stime, &p.vsize);
                    processes[count++] = p;
                    fclose(stat);
                }
            }
        }
    }
    closedir(proc);

    printf("PID\tState\tUserTime\tSysTime\t\tVirtMem\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%c\t%lu\t\t%lu\t\t%lu\n",
            processes[i].pid, processes[i].state, processes[i].utime, processes[i].stime, processes[i].vsize);
    }

    return 0;
}