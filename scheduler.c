#include <stdio.h>
#include "scheduler.h"

// Sort jobs by arrival time.
// If arrival times are equal, original input order is maintained.
static void sort_by_arrival(Job jobs[], int order[], int n) {
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (jobs[order[j]].arrival_time >
                jobs[order[j + 1]].arrival_time) {
                int temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }
}

// Reset job details before each algorithm.
static void reset_jobs(Job jobs[], int n) {
    for (int i = 0; i < n; i++) {
        jobs[i].remaining_time = jobs[i].burst_time;
        jobs[i].completion_time = 0;
        jobs[i].turnaround_time = 0;
        jobs[i].waiting_time = 0;
        jobs[i].status = 0;
    }
}

// Calculate and display scheduling metrics.
static void print_metrics(Job jobs[], int n) {
    double total_tat = 0;
    double total_wt = 0;

    printf("\nJob\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("J%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               jobs[i].id,
               jobs[i].arrival_time,
               jobs[i].burst_time,
               jobs[i].priority,
               jobs[i].completion_time,
               jobs[i].turnaround_time,
               jobs[i].waiting_time);

        total_tat += jobs[i].turnaround_time;
        total_wt += jobs[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

// Calculate completion, turnaround and waiting times.
static void calculate_metrics(Job *job, int time) {
    job->completion_time = time;
    job->turnaround_time = job->completion_time - job->arrival_time;
    job->waiting_time = job->turnaround_time - job->burst_time;
    job->remaining_time = 0;
    job->status = 2;
}

// 1. FIRST COME FIRST SERVE (FCFS)
void fcfs_schedule(Job jobs[], int n) {
    if (n <= 0 || n > MAX_JOBS) {
        printf("Invalid number of jobs.\n");
        return;
    }

    int order[MAX_JOBS];
    int time = 0;

    reset_jobs(jobs, n);
    sort_by_arrival(jobs, order, n);

    printf("\n========== FCFS SCHEDULING ==========\n");
    printf("\nExecution Timeline:\n");

    for (int i = 0; i < n; i++) {
        Job *job = &jobs[order[i]];

        if (time < job->arrival_time) {
            time = job->arrival_time;
        }

        int start = time;
        job->status = 1;
        time += job->burst_time;

        printf("J%d [%d - %d]\n", job->id, start, time);

        calculate_metrics(job, time);
    }

    print_metrics(jobs, n);
}

// 2. ROUND ROBIN SCHEDULING
void round_robin_schedule(Job jobs[], int n, int quantum) {
    if (n <= 0 || n > MAX_JOBS || quantum <= 0) {
        printf("Invalid number of jobs or time quantum.\n");
        return;
    }

    int order[MAX_JOBS];
    int queue[MAX_JOBS + 1];
    int front = 0, rear = 0;
    int completed = 0;
    int next = 0;
    int time = 0;

    reset_jobs(jobs, n);
    sort_by_arrival(jobs, order, n);

    printf("\n========== ROUND ROBIN SCHEDULING ==========\n");
    printf("Time Quantum: %d\n", quantum);
    printf("\nExecution Timeline:\n");

    // Start at the first job's arrival time.
    time = jobs[order[0]].arrival_time;

    // Add all jobs that have arrived to the ready queue.
    while (next < n &&
           jobs[order[next]].arrival_time <= time) {
        queue[rear] = order[next];
        rear = (rear + 1) % (MAX_JOBS + 1);
        next++;
    }

    while (completed < n) {

        // If nobody is ready, move time to the next arrival.
        if (front == rear) {
            time = jobs[order[next]].arrival_time;

            while (next < n &&
                   jobs[order[next]].arrival_time <= time) {
                queue[rear] = order[next];
                rear = (rear + 1) % (MAX_JOBS + 1);
                next++;
            }
        }

        // Take the first job from the ready queue.
        int index = queue[front];
        front = (front + 1) % (MAX_JOBS + 1);

        Job *job = &jobs[index];
        job->status = 1;

        int start = time;
        int run_time = (job->remaining_time < quantum)
                       ? job->remaining_time : quantum;

        time += run_time;
        job->remaining_time -= run_time;

        printf("J%d [%d - %d]\n", job->id, start, time);

        // Add newly arrived jobs before re-adding the current job.
        while (next < n &&
               jobs[order[next]].arrival_time <= time) {
            queue[rear] = order[next];
            rear = (rear + 1) % (MAX_JOBS + 1);
            next++;
        }

        if (job->remaining_time == 0) {
            calculate_metrics(job, time);
            completed++;
        } else {
            job->status = 0;

            queue[rear] = index;
            rear = (rear + 1) % (MAX_JOBS + 1);
        }
    }

    print_metrics(jobs, n);
}

// 3. NON-PREEMPTIVE PRIORITY SCHEDULING
// Smaller priority number means higher priority.
void priority_schedule(Job jobs[], int n) {
    if (n <= 0 || n > MAX_JOBS) {
        printf("Invalid number of jobs.\n");
        return;
    }

    int completed = 0;
    int time = 0;

    reset_jobs(jobs, n);

    printf("\n========== PRIORITY SCHEDULING ==========\n");
    printf("Rule: Smaller priority number = higher priority.\n");
    printf("Tie-break: Earlier arrival, then original input order.\n");
    printf("\nExecution Timeline:\n");

    while (completed < n) {
        int selected = -1;

        // Find the highest-priority job that has already arrived.
        for (int i = 0; i < n; i++) {
            if (jobs[i].remaining_time > 0 &&
                jobs[i].arrival_time <= time) {

                if (selected == -1 ||
                    jobs[i].priority < jobs[selected].priority ||
                    (jobs[i].priority == jobs[selected].priority &&
                     jobs[i].arrival_time < jobs[selected].arrival_time)) {

                    selected = i;
                }
            }
        }

        // If no job has arrived, advance the clock.
        if (selected == -1) {
            int next_arrival = -1;

            for (int i = 0; i < n; i++) {
                if (jobs[i].remaining_time > 0 &&
                    (next_arrival == -1 ||
                     jobs[i].arrival_time < next_arrival)) {
                    next_arrival = jobs[i].arrival_time;
                }
            }

            time = next_arrival;
            continue;
        }

        Job *job = &jobs[selected];

        int start = time;
        job->status = 1;
        time += job->burst_time;

        printf("J%d [ %d - %d ]\n", job->id, start, time);

        calculate_metrics(job, time);
        completed++;
    }

    print_metrics(jobs, n);
}
