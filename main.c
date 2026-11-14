#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "scheduler.h"
#include "banker.h"
#include "logger.h"
#include "ipc.h"
#include "worker.h"
#include "limits.h"

int main(void) {
    int choice;
    Job jobs[MAX_JOBS];
    int n, quantum;
    int logger_used = 0;

    while (1) {
        printf("\n====================================\n");
        printf("          CAMPUS COMPUTE\n");
        printf(" INTELLIGENT JOB AND RESOURCE SYSTEM\n");
        printf("====================================\n");

        printf("\n--- CPU SCHEDULING ---\n");
        printf("1. FCFS Scheduling\n");
        printf("2. Round Robin Scheduling\n");
        printf("3. Priority Scheduling\n");
        printf("4. Banker's Algorithm\n");

        printf("\n--- PROCESS MANAGEMENT ---\n");
        printf("5. Thread Logger\n");
        printf("6. Shared Memory and Semaphores\n");
        printf("7. Normal Worker Process\n");
        printf("8. Simulated Worker Failure\n");
        printf("9. Resource Limits\n");
        printf("10. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {

            case 1:
            case 2:
            case 3:

                printf("\nEnter number of jobs: ");

                if (scanf("%d", &n) != 1 ||
                    n <= 0 || n > MAX_JOBS) {
                    printf("Invalid number of jobs.\n");
                    return 1;
                }

                for (int i = 0; i < n; i++) {
                    jobs[i].id = i + 1;

                    printf("\nJob J%d\n", i + 1);

                    printf("Arrival Time: ");
                    if (scanf("%d", &jobs[i].arrival_time) != 1 ||
                        jobs[i].arrival_time < 0) {
                        printf("Invalid arrival time.\n");
                        return 1;
                    }

                    printf("Burst Time: ");
                    if (scanf("%d", &jobs[i].burst_time) != 1 ||
                        jobs[i].burst_time <= 0) {
                        printf("Invalid burst time.\n");
                        return 1;
                    }

                    printf("Priority: ");
                    if (scanf("%d", &jobs[i].priority) != 1) {
                        printf("Invalid priority.\n");
                        return 1;
                    }
                }

                if (choice == 1) {
                    fcfs_schedule(jobs, n);
                }
                else if (choice == 2) {
                    printf("Enter Time Quantum: ");

                    if (scanf("%d", &quantum) != 1 ||
                        quantum <= 0) {
                        printf("Invalid quantum.\n");
                        return 1;
                    }

                    round_robin_schedule(jobs, n, quantum);
                }
                else {
                    priority_schedule(jobs, n);
                }

                break;

            case 4:
                bankers_algorithm();
                break;

            case 5:
                if (logger_used) {
                    printf("\nLogger has already been executed.\n");
                    break;
                }

                printf("\n--- THREAD LOGGER ---\n");

                init_logger();

                push_log("CampusCompute: Logger initialized.");
                push_log("CampusCompute: Thread logger running.");
                push_log("CampusCompute: Event recorded successfully.");

                close_logger();
                logger_used = 1;

                printf("Check log.txt for recorded events.\n");
                break;

            case 6:
                printf("\n--- SHARED MEMORY IPC ---\n");
                demonstrate_shared_memory();
                break;

            case 7:
                printf("\n--- NORMAL WORKER ---\n");
                spawn_normal_worker();
                break;

            case 8:
                printf("\n--- WORKER FAILURE DETECTION ---\n");
                spawn_failed_worker();
                break;

            case 9: {
                printf("\n--- RESOURCE LIMITS ---\n");

                pid_t pid = fork();

                if (pid < 0) {
                    perror("fork failed");
                }
                else if (pid == 0) {
                    demonstrate_resource_limits();
                    fflush(stdout);
                    _exit(0);
                }
                else {
                    int status;
                    waitpid(pid, &status, 0);
                    printf("Resource limit demonstration completed in child process.\n");
                }

                break;
            }

            case 10:
                printf("\nThank you for using CampusCompute!\n");
                return 0;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}
