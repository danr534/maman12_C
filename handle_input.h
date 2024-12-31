#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 50

/* get the next line from the input and store it in the argument array */
void get_line(char line[]);

/* decode the line into a command and store command number in the second argument and variables names in the last 2 arguments.
   return 1 if the command is valid and 0 otherwise */
int decode_line(char line[], int *command, char *x, char *y, double *z, double *w);