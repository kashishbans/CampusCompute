#ifndef LOGGER_H
#define LOGGER_H

#define BUFFER_SIZE 5

void init_logger();
void push_log(const char *message);
void close_logger();

#endif

