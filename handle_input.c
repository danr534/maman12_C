#include "handle_input.h"

/* number of commands */
#define NUM_COMMANDS 9

const char *commands[] = {"read_comp", "print_comp", "add_comp", "sub_comp", "mult_comp_real", "mult_comp_img", "mult_comp_comp", "abs_comp", "stop"};

/* remove all blanks in a line */
void remove_whites(char *line);

/* find command number in a line */
int find_command(char *line);

/* decode stop command */
int decode_stop(char *line);

/* decode commands that use 1 variable which are print_comp and abs_comp*/
int decode_1_variable(char *line);

/* decode commands that use 2 variables which are add_comp, sub_comp and mult_comp_comp */
int decode_2_variables(char *line, char *var2);

/* decode commands that use 1 variable and 1 number which are mult_comp_real and mult_comp_img*/
int decode_mult(char *line, double *num1);

/* decode commands that use 1 variable and 2 numbers which is only read_comp */
int decode_read_comp(char *line, double *num1, double *num2);

void get_line(char line[]) {
    printf("Please enter a command:\n");

    /* check if reached EOF */
    if(fgets(line, LINE_LEN, stdin) == NULL) {
        printf("Reached EOF before stop command.\nThe program has finished.");
        exit(0);
    }

    /* print the line */
    printf("The line you entered is:\n");
    printf("%s", line);
}

int decode_line(char line[], int *command, char *var1, char *var2, double *num1, double *num2) {
    int c; /* command number */

    while(*line == ' ' || *line == '\t' || *line == '\n') line++; /* find a non white letter */
    if(*line == '\0') return 0; /* check if the line is white letters only*/

    /* check if the command is valid */
    c = find_command(line);
    if(c == -1) {
        printf("Undefined command name.\n");
        return 0;
    }
    *command = c;
    line += strlen(commands[c]);

    /* check if the command is stop */
    if(c == STOP) return decode_stop(line);

    /* check for a space or tab after command */
    if(*line != ' ' && *line != '\t') {
        printf("Missing space after command.\n");
        return 0;
    }
    remove_whites(line);
    /* check if the first variable is valid */
    if(*line == '\0') {
        printf("Missing parameter.\n");
        return 0;
    }
    if(*line == ',') {
        printf("Illegal comma.\n");
        return 0;
    }
    if(*line < 'A' || *line > 'F') {
        printf("Undefined complex variable.\n");
        return 0;
    }
    *var1 = *line;
    line++;

    /* check for 1 variable commands */
    if(c == PRINT_COMP || c == ABS_COMP) return decode_1_variable(line);

    /* check for comma */
    if(*line != ',') {
        printf("Missing comma.\n");
        return 0;
    }
    line++;

    /* check for null terminator */
    if(*line == '\0') {
        printf("Missing parameter.\n");
        return 0;
    }
    /* check for multiple consecutive commas */
    if(*line == ',') {
        printf("Multiple consecutive commas\n");
        return 0;
    }

    /* divide into 3 cases */
    if(c == ADD_COMP || c == SUB_COMP || c == MULT_COMP_COMP) return decode_2_variables(line, var2);
    else if(c == MULT_COMP_REAL || c == MULT_COMP_IMG) return decode_mult(line, num1);
    else return decode_read_comp(line, num1, num2);

    return 1;
}

void execute_line(complex variables[], int command, char var1, char var2, double num1, double num2) {
    complex *var1Ptr, *var2Ptr; /* pointers to the complex variables given in the line */
    var1Ptr = &variables[var1 - 'A'];
    if(command == PRINT_COMP) print_comp(*var1Ptr);
    else if(command == ABS_COMP) abs_comp(*var1Ptr);
    else if(command == ADD_COMP || command == SUB_COMP || command == MULT_COMP_COMP) {
        var2Ptr = &variables[var2 - 'A'];
        if(command == ADD_COMP) add_comp(*var1Ptr, *var2Ptr);
        if(command == SUB_COMP) sub_comp(*var1Ptr, *var2Ptr);
        if(command == MULT_COMP_COMP) mult_comp_comp(*var1Ptr, *var2Ptr);
    }
    else if(command == MULT_COMP_REAL) mult_comp_real(*var1Ptr, num1);
    else if(command == MULT_COMP_IMG) mult_comp_img(*var1Ptr, num1);
    else read_comp(var1Ptr, num1, num2); 
}

int find_command(char *line) {
    int i = 0;
    for(i = 0; i < NUM_COMMANDS; i++) {
        if(!strncmp(line, commands[i], strlen(commands[i]))) return i;
    }
    return -1;
}

int decode_stop(char *line) {
    remove_whites(line);
    if(*line == '\0') {
        printf("\nExiting program with stop command.");
        return 1;
    }
    else {
        printf("Extraneous text after end of command.\n");
        return 0;
    }
}

int decode_1_variable(char *line) {
    if(*line == '\0') return 1;
    else {
        printf("Extraneous text after end of command.\n");
        return 0;
    }
}

void remove_whites(char *line) {
    int i = 0, j = 0;
    while (line[i] != '\0') {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') line[j++] = line[i];
        i++;
    }
    line[j] = '\0';
}

int decode_2_variables(char *line, char *var2) {
    /* check if the second variable is valid*/
    if(*line < 'A' || *line > 'F') {
        printf("Undefined complex variable.\n");
        return 0;
    }
    *var2 = *line;
    line++;

    /* check for extraneous text */
    if(*line != '\0') {
        printf("Extraneous text after end of command.\n");
        return 0;
    }
    return 1;
}

int decode_mult(char *line, double *num1) {
    char *endPtr; /* pointer to the end of the number in line*/
    double value; /* the value of the number */

    /* check if the second parameter is a number */
    value = strtod(line, &endPtr);
    if(endPtr == line) {
        printf("Invalid parameter - not a number\n");
        return 0;
    }
    if(*endPtr != '\0') {
        printf("Extraneous text after end of command.\n");
        return 0;
    }

    *num1 = value;
    return 1;
}

int decode_read_comp(char *line, double *num1, double *num2) {
    char *endPtr; /* pointer to the end of the number in line*/
    double value; /* the value of the number */

    /* check if the second parameter is a number */
    value = strtod(line, &endPtr);
    if(endPtr == line) {
        printf("Invalid parameter - not a number\n");
        return 0;
    }
    if(*endPtr != ',') {
        printf("Missing comma.\n");
        return 0;
    }
    *num1 = value;
    line = endPtr + 1;

    /* check if there is a third parameter */
    if(*line == '\0') {
        printf("Missing parameter.\n");
        return 0;
    }

    /* check for multiple consecutive commas */
    if(*line == ',') {
        printf("Multiple consecutive commas\n");
        return 0;
    }

    /* check if the third parameter is a number */
    value = strtod(line, &endPtr);
    if(endPtr == line) {
        printf("Invalid parameter - not a number\n");
        return 0;
    }
    if(*endPtr != '\0') {
        printf("Extraneous text after end of command.\n");
        return 0;
    }
    *num2 = value;
    return 1;
    
}