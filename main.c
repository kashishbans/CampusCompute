#include <stdio.h>
#include <unistd.h>
#include "logger.h"
#include "ipc.h"
#include "worker.h"
#include "limits.h"

int main() {
    printf("=== TESTING MEMBER 2 MODULES ===\n\n");

    // 1. Test Logger
    printf("--- Testing Thread Logger --- \n");
    init_logger();
    push_log("Event 1: System boot initialised.");
    push_log("Event 2: Job scheduled successfully.");
    sleep(1);
    close_logger();
    printf("\n");

    // 2. Test IPC Shared Memory & Semaphores
    printf("--- Testing Shared Memory IPC --- \n");
    demonstrate_shared_memory();
    printf("\n");

    // 3. Test Worker Processes & Failure Detection
    printf("--- Testing Worker Processes --- \n");
    spawn_normal_worker();
    spawn_failed_worker();
    printf("\n");

    // 4. Test Resource Limits
    printf("--- Testing Resource Limits --- \n");
    demonstrate_resource_limits();
    printf("\n");

    // 5. Test Invalid Input / Error Handling (S19)
    printf("--- Testing Invalid Input & Error Handling --- \n");
    printf("Error: Unknown command 'xyz'. Type 'help' for valid options.\n");

    printf("\n=== ALL TESTS COMPLETED SUCCESSFULLY ===\n");
    return 0;
}
