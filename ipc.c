#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <unistd.h>
#include "ipc.h"

#define SHM_NAME "/campus_compute_shm"
#define SEM_NAME "/campus_compute_sem"
#define SHM_SIZE 1024

void demonstrate_shared_memory() {
    // Create shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        return;
    }
    ftruncate(shm_fd, SHM_SIZE);

    // Create named semaphore
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open failed");
        close(shm_fd);
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
    } else if (pid == 0) {
        // Child process: write data to shared memory
        sem_wait(sem);
        void *ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (ptr != MAP_FAILED) {
            snprintf((char *)ptr, SHM_SIZE, "Hello from Child Process via Shared Memory!");
            munmap(ptr, SHM_SIZE);
        }
        sem_post(sem);
        exit(0);
    } else {
        // Parent process: wait for child, then read shared memory
        waitpid(pid, NULL, 0);

        sem_wait(sem);
        void *ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        if (ptr != MAP_FAILED) {
            printf("[IPC Shared Memory] Read from child: %s\n", (char *)ptr);
            munmap(ptr, SHM_SIZE);
        }
        sem_post(sem);

        // Cleanup IPC handles
        sem_close(sem);
        sem_unlink(SEM_NAME);
        shm_unlink(SHM_NAME);
        printf("[IPC] Shared memory and semaphores cleaned up successfully.\n");
    }
}

