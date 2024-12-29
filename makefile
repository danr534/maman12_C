# Compiler Flags
CFLAGS = -Wall -ansi -pedantic -std=c90


mycomp: mycomp.o complex.o
	gcc $(CFLAGS) mycomp.o complex.o -o mycomp -lm

mycomp.o: mycomp.c complex.h
	gcc $(CFLAGS) -c mycomp.c -o mycomp.o

complex.o: complex.c complex.h
	gcc $(CFLAGS) -c complex.c -o complex.o
