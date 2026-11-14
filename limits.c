#include <stdio.h>
#include <sys/resource.h>
#include "limits.h"

void demonstrate_resource_limits() {
    struct rlimit old_lim, new_lim;

    // Get current CPU time limit
    if (getrlimit(RLIMIT_CPU, &old_lim) == 0) {
        printf("[Resource Limits] Current CPU limit: soft=%ld, hard=%ld\n", 
               (long)old_lim.rlim_cur, (long)old_lim.rlim_max);
    }

    // Set a modified sample limit (e.g., 10 seconds of CPU time)
    new_lim.rlim_cur = 10;
    new_lim.rlim_max = 20;
    if (setrlimit(RLIMIT_CPU, &new_lim) == 0) {
        printf("[Resource Limits] Successfully applied new CPU time limit (soft: 10s).\n");
    } else {
        perror("setrlimit failed");
    }
}

