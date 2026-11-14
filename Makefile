CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -pthread

TARGET = campuscompute

SOURCES = main.c scheduler.c banker.c logger.c ipc.c worker.c limits.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
