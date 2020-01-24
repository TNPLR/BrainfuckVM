CC=gcc
CFLAGS=-O0 -Wall -ggdb

.PHONY: all clean
all: bvm
bvm: main.o stack.o
	${CC} ${CFLAGS} $^ -o $@
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@
clean:
	rm -f *.o bvm
