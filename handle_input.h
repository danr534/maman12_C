#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"

/* maximum length of a line */
#define LINE_LEN 50

/* numbers to identify the command names */
enum commands_names {READ_COMP, PRINT_COMP, ADD_COMP, SUB_COMP, MULT_COMP_REAL, MULT_COMP_IMG, MULT_COMP_COMP, ABS_COMP, STOP};

  
/* get the next line from the input.
   params:
   line - character array to save the next line */
void get_line(char line[]);

/* decode the line into a command.
   params:
   command - integer to save the command number
   var1 - char to save the first variable name (if exists)
   var2 - char to save the second variable name (if exists)
   num1 - double to save the first number parameter (if exists)
   num2 - double to save the second number parameter (if exists)
   returns: 1 if the command is valid and 0 otherwise */
int decode_line(char line[], int *command, char *var1, char *var2, double *num1, double *num2);

/* execute the corresponding function to the command in the line with the corresponding parameters
   params:
   variables - complex array including the values of all the variables 
   command - command number
   var1 - first variable name (if exists)
   var2 - second variable name (if exists)
   num1 - first number parmeter (if exists) 
   num2 - second number parameter (if exists) */
void execute_line(complex variables[], int command, char var1, char var2, double num1, double num2);