#include "complex.h"
#include "handle_input.h"


int main()
{
	complex A = {0, 0}, B = {0, 0}, C = {0, 0}, D = {0, 0}, E = {0, 0}, F = {0, 0};
    char line[LINE_LEN];
    int command;
    char x, y;
    double z, w;
    int is_valid;
    get_line(line);
    is_valid = decode_line(line, &command, &x, &y, &z, &w);
    printf("decode return: %d, command number: %d.\n", is_valid, command);
	return 0;
}
