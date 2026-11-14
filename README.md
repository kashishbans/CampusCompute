# CampusCompute
### Intelligent Job Scheduling and Resource Management System

## 1. Project Overview

CampusCompute is a C-based Operating Systems project that demonstrates CPU scheduling, process management, inter-process communication, thread synchronization, and resource management.

The project combines multiple Operating System concepts into one interactive menu-driven application.

It demonstrates how an operating system manages processes, schedules jobs, coordinates threads, shares data between processes, and controls resource usage.

## 2. Features

### A. CPU Scheduling

The project implements three CPU scheduling algorithms:

- **First Come First Serve (FCFS):** Executes processes in the order in which they arrive.
- **Round Robin (RR):** Allocates CPU time to processes using a fixed time quantum.
- **Priority Scheduling:** Executes processes based on their priority.

### B. Banker's Algorithm

Implements the Banker's Algorithm for deadlock avoidance.

It:
- Calculates the Need matrix.
- Checks whether the system is in a safe state.
- Determines a safe execution sequence, if one exists.
- Identifies unsafe states.

### C. Thread Logger

Demonstrates the Producer-Consumer problem using POSIX threads.

It uses:
- Mutex locks.
- Condition variables.
- A bounded buffer.
- Producer-consumer synchronization.
- Thread joining and resource cleanup.

Events are recorded in `log.txt`.

### D. Shared Memory and Semaphores

Demonstrates Inter-Process Communication (IPC) using:

- POSIX shared memory.
- Memory mapping using `mmap()`.
- Named semaphores.
- Process creation using `fork()`.
- Shared memory cleanup.

A child process writes a message into shared memory, which the parent process reads.

### E. Process Management

Demonstrates process creation and termination using:

- `fork()`
- `waitpid()`
- Exit status checking.

Includes:
- Normal worker process execution.
- Simulated worker failure using a non-zero exit code.

### F. Resource Limits

Demonstrates resource management using `getrlimit()` and `setrlimit()`.

The implementation applies CPU time limits in an isolated child process.

## 3. Technologies Used

- **Programming Language:** C
- **Operating System:** Linux (Ubuntu)
- **Compiler:** GCC
- **Build Tool:** GNU Make
- **Threading:** POSIX Threads (pthreads)
- **IPC:** POSIX Shared Memory and Semaphores
- **Version Control:** Git and GitHub

## 4. Project Structure

```text
CampusCompute/
│
├── main.c
├── scheduler.c
├── scheduler.h
├── banker.c
├── banker.h
│
├── logger.c
├── logger.h
├── ipc.c
├── ipc.h
├── worker.c
├── worker.h
├── limits.c
├── limits.h
│
├── Makefile
├── .gitignore
└── README.md
```

## 5. Compilation and Execution

### Prerequisites

- Linux environment (Ubuntu recommended).
- GCC compiler.
- GNU Make.
- POSIX thread support.

### Step 1: Clone the repository

```bash
git clone https://github.com/kashishbans/CampusCompute.git
cd CampusCompute
```

### Step 2: Compile the project

```bash
make
```

### Step 3: Run the application

```bash
./campuscompute
```

### Step 4: Clean generated files

```bash
make clean
```

## 6. Application Menu

The application provides the following options:

| Option | Function |
|---|---|
| 1 | FCFS Scheduling |
| 2 | Round Robin Scheduling |
| 3 | Priority Scheduling |
| 4 | Banker's Algorithm |
| 5 | Thread Logger |
| 6 | Shared Memory and Semaphores |
| 7 | Normal Worker Process |
| 8 | Simulated Worker Failure |
| 9 | Resource Limits |
| 10 | Exit |

## 7. Learning Outcomes

Through this project, we demonstrate practical implementation of:

- CPU scheduling algorithms.
- Deadlock avoidance.
- Multithreading and synchronization.
- Producer-Consumer problem.
- Inter-Process Communication.
- Shared memory and semaphore synchronization.
- Process creation and termination.
- Resource limitation and management.

## 8. Team Contributions

The project was developed collaboratively, with different modules implemented and integrated by team members.

The final application combines CPU scheduling and deadlock avoidance with process management, threading, IPC, and resource management.

## 9. Conclusion

CampusCompute brings together fundamental Operating System concepts in a single interactive application.

It provides a practical demonstration of how operating systems schedule processes, coordinate concurrent execution, communicate between processes, avoid unsafe resource allocation, and manage system resources.
