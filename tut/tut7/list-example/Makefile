CC=clang
CFLAGS=-g -std=c11 -Wall -Werror

TARGET=tasks

.PHONY: clean

all: $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f *.o

list.o: list.c
	$(CC) -c $(CFLAGS) $^ -o $@

tasks.o: tasks.c
	$(CC) -c $(CFLAGS) $^ -o $@

tasks: tasks.o list.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
