CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c99
TARGET = campus_compute

SRCS = main.c logger.c ipc.c worker.c limits.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS) $(TARGET) log.txt

.PHONY: all clean

