#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "logger.h"

#define MAX_MSG_LEN 256

typedef struct {
    char messages[BUFFER_SIZE][MAX_MSG_LEN];
    int head;
    int tail;
    int count;
} LogQueue;

static LogQueue log_queue;
static pthread_mutex_t mutex;
static pthread_cond_t not_full;
static pthread_cond_t not_empty;
static pthread_t consumer_thread;
static int keep_running = 1;
static FILE *log_file = NULL;

void *consumer_task(void *arg) {
    (void)arg;
    log_file = fopen("log.txt", "w");
    if (!log_file) {
        perror("Failed to open log.txt");
        return NULL;
    }

    while (1) {
        pthread_mutex_lock(&mutex);
        while (log_queue.count == 0 && keep_running) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        if (log_queue.count == 0 && !keep_running) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        char msg[MAX_MSG_LEN];
        strcpy(msg, log_queue.messages[log_queue.head]);
        log_queue.head = (log_queue.head + 1) % BUFFER_SIZE;
        log_queue.count--;

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);

        fprintf(log_file, "%s\n", msg);
        fflush(log_file);
    }

    if (log_file) {
        fclose(log_file);
    }
    return NULL;
}

void init_logger() {
    log_queue.head = 0;
    log_queue.tail = 0;
    log_queue.count = 0;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    pthread_create(&consumer_thread, NULL, consumer_task, NULL);
}

void push_log(const char *message) {
    pthread_mutex_lock(&mutex);
    while (log_queue.count == BUFFER_SIZE) {
        pthread_cond_wait(&not_full, &mutex);
    }

    strcpy(log_queue.messages[log_queue.tail], message);
    log_queue.tail = (log_queue.tail + 1) % BUFFER_SIZE;
    log_queue.count++;

    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
}

void close_logger() {
    pthread_mutex_lock(&mutex);
    keep_running = 0;
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);

    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    printf("[Logger] Producer-consumer threads joined and resources cleaned up successfully.\n");
}
