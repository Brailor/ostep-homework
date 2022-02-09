
CC = gcc
CFLAGS = -Wall -Wextra
TARGETS := measure_syscall.out

all: $(TARGETS)

%.out: %.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f ./*.out