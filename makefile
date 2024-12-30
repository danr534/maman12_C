# Compiler Flags
CFLAGS = -Wall -ansi -pedantic -std=c90


mycomp: mycomp.o handle_input.o complex.o
	gcc $(CFLAGS) mycomp.o handle_input.o complex.o -o mycomp -lm

mycomp.o: mycomp.c handle_input.h complex.h 
	gcc $(CFLAGS) -c mycomp.c -o mycomp.o

handle_input.o: handle_input.c handle_input.h complex.h
	gcc $(CFLAGS) -c handle_input.c -o handle_input.o

complex.o: complex.c complex.h
	gcc $(CFLAGS) -c complex.c -o complex.o
