CC=gcc
FLAGS=-Wall -Werror -g 
DEBUG=-fsanitize=address

TARGET=tasks

.PHONY: clean

clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f debug
	rm -f test

all: $(TARGET)

main.o: main.c
	$(CC) -c $(FLAGS) $^ -o $@

stack.o: stack.c
	$(CC) -c $(FLAGS) $^ -o $@

tasks: main.o stack.o
	$(CC) $(FLAGS) $(LDFLAGS) $^ -o $@

debug: main.c stack.c
	$(CC) $(FLAGS) $(DEBUG) $^ -o $@

test: stack.c test.c
	$(CC) $(FLAGS) $(LDFLAGS) $^ -o $@
	./$@ all
