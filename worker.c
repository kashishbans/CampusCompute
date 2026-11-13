#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "worker.h"

void spawn_normal_worker() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
    } else if (pid == 0) {
        printf("[Worker] Child process started (PID: %d). Performing task...\n", getpid());
        sleep(1);
        exit(0); // Normal completion
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("[Worker Detection] Child %d completed normally with exit code %d.\n", pid, WEXITSTATUS(status));
        }
    }
}

void spawn_failed_worker() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
    } else if (pid == 0) {
        printf("[Worker] Simulated failure child started (PID: %d). Encountering error...\n", getpid());
        sleep(1);
        exit(42); // Controlled simulated failure exit code
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("[Worker Detection] Simulated failure caught! Child %d exited with error code %d.\n", pid, WEXITSTATUS(status));
        }
    }
}

