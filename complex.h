#include <stdio.h>
#include <math.h>

typedef struct complex {
    double real;
    double img;
} complex;

/* Assign real and imginary values to a complex number */ 
void read_comp(complex *c, double real, double img);

/* Print a complex number */
void print_comp(complex c);

/* Add 2 complex numbers and print the result */
void add(complex c1, complex c2);

/* Subtract 2 complex numbers and print the result */
void sub(complex c1, complex c2);

/* Multiply a complex number with a real number and print the result */
void mult_comp_real(complex c, double a);

/* Multiply a complex number with an imaginary number and print the result */
void mult_comp_img(complex c, double b);

/* Multiply 2 complex numbers and print the result */
void mult_comp_comp(complex c1, complex c2);

/* Print the absolute value of a complex number */
void abs_comp(complex c);
