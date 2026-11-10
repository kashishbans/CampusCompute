#include <stdio.h>
#include "scheduler.h"
#include "banker.h"

int main(void) {
    int choice;
    Job jobs[MAX_JOBS];
    int n, quantum;

    while (1) {
        printf("\n====================================\n");
        printf("         CAMPUS COMPUTE\n");
        printf("      CPU SCHEDULING SYSTEM\n");
        printf("====================================\n");

        printf("1. FCFS Scheduling\n");
        printf("2. Round Robin Scheduling\n");
        printf("3. Priority Scheduling\n");
        printf("4. Banker's Algorithm\n");
        printf("5. Exit\n");

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

                    printf("Priority (smaller number = higher priority): ");
                    if (scanf("%d", &jobs[i].priority) != 1) {
                        printf("Invalid priority.\n");
                        return 1;
                    }
                }

                if (choice == 1) {
                    fcfs_schedule(jobs, n);
                }
                else if (choice == 2) {
                    printf("\nEnter Time Quantum: ");

                    if (scanf("%d", &quantum) != 1 ||
                        quantum <= 0) {
                        printf("Invalid time quantum.\n");
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
                printf("\nThank you for using CampusCompute!\n");
                return 0;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}
