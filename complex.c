#include "complex.h"

void read_comp(complex *c, double real, double img) {
	c->real = real;
	c->img = img;
}

void print_comp(complex c) {
	if(c.img >= 0) printf("%.2f + (%.2f)i\n", c.real, c.img);
	else printf("%.2f - (%.2f)i\n", c.real, -c.img);
}

void add_comp(complex c1, complex c2) {
	complex tmp;
	read_comp(&tmp, c1.real + c2.real, c1.img + c2.img);
	print_comp(tmp);
}

void sub_comp(complex c1, complex c2) {
	complex tmp;
	read_comp(&tmp, c1.real - c2.real, c1.img - c2.img);
	print_comp(tmp);
}

void mult_comp_real(complex c, double a) {
	complex tmp;
	read_comp(&tmp, a*c.real, a*c.img);
	print_comp(tmp);
}

void mult_comp_img(complex c, double b) {
	complex tmp;
	read_comp(&tmp, -b*(c.img), b*c.real);
	print_comp(tmp);
}

void mult_comp_comp(complex c1, complex c2) {
	complex tmp;
	read_comp(&tmp, c1.real*c2.real - c1.img*c2.img, c1.real*c2.img + c2.real*c1.img);
	print_comp(tmp);
}

void abs_comp(complex c) {
    printf("%.2f\n", sqrt(c.real*c.real + c.img*c.img));
}
