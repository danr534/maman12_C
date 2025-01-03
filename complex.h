#include <stdio.h>
#include <math.h>

/* structure of a complex number */
typedef struct complex {
    double real;
    double img;
} complex;

/* Assign real and imginary values to a complex number.
   params:
   c - a pointer to a complex number
   real - the real component to assign 
   img - the imaginary component to assign */ 
void read_comp(complex *c, double real, double img);

/* Print a complex number.
   params:
   c - a complex number */
void print_comp(complex c);

/* Add 2 complex numbers and print the result.
   params: 
   c1 - first complex number 
   c2 - second complex number */
void add_comp(complex c1, complex c2);

/* Subtract 2 complex numbers and print the result.
   params: 
   c1 - first complex number 
   c2 - second complex number */
void sub_comp(complex c1, complex c2);

/* Multiply a complex number with a real number and print the result.
   params: 
   c - a complex number 
   a - the real number */
void mult_comp_real(complex c, double a);

/* Multiply a complex number with an imaginary number and print the result.
   params:
   c - a complex number
   b - the imaginary component of the imaginary number */
void mult_comp_img(complex c, double b);

/* Multiply 2 complex numbers and print the result.
   params: 
   c1 - first complex number 
   c2 - second complex number */
void mult_comp_comp(complex c1, complex c2);

/* Print the absolute value of a complex number.
   c - a complex number */
void abs_comp(complex c);
