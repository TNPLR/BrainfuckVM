CC=gcc
CFLAG=-O3 -c

all: main.o
	gcc main.o -o bvm
main.o:
	${CC} ${CFLAG} main.c -o main.o
clean:
	rm -f *.o bvm
