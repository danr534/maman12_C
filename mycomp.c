#include "complex.h"

int main()
{
	complex c1;
	complex c2;
	
	read_comp(&c1, 2, 1);
	read_comp(&c2, 2, 3);
	abs_comp(c1);
	
	return 0;
}
