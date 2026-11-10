#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_JOBS 100

// Structure to store information about each job
typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int priority;

    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;

    int status;
} Job;

// CPU Scheduling Functions
void fcfs_schedule(Job jobs[], int n);

void round_robin_schedule(Job jobs[], int n, int quantum);

void priority_schedule(Job jobs[], int n);

#endif

