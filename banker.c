#include <stdio.h>
#include "banker.h"

void bankers_algorithm(void) {
    int n, m;
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int maximum[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safe_sequence[MAX_PROCESSES];

    printf("\n========== BANKER'S ALGORITHM ==========\n");

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return;
    }

    printf("Enter number of resource types: ");
    if (scanf("%d", &m) != 1 || m <= 0 || m > MAX_RESOURCES) {
        printf("Invalid number of resources.\n");
        return;
    }

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &allocation[i][j]) != 1 || allocation[i][j] < 0) {
                printf("Invalid allocation value.\n");
                return;
            }
        }
    }

    printf("\nEnter Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &maximum[i][j]) != 1 ||
                maximum[i][j] < allocation[i][j]) {
                printf("Invalid maximum value.\n");
                return;
            }
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    printf("\nEnter Available Resources: ");
    for (int j = 0; j < m; j++) {
        if (scanf("%d", &available[j]) != 1 || available[j] < 0) {
            printf("Invalid available resource value.\n");
            return;
        }
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int completed = 0;

    while (completed < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int possible = 1;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        possible = 0;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }

                    safe_sequence[completed++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nSystem is NOT in a safe state.\n");
            return;
        }
    }

    printf("\nSystem is in a SAFE state.\n");
    printf("Safe Sequence: ");

    for (int i = 0; i < n; i++) {
        printf("P%d", safe_sequence[i]);
        if (i < n - 1) {
            printf(" -> ");
        }
    }

    printf("\n");
}
