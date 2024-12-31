#include "handle_input.h"

#define NUM_COMMANDS 9
#define NUM_VARIABLES 6

/* numbers to identify the command names */
enum names {READ_COMP, PRINT_COMP, ADD_COMP, SUB_COMP, MULT_COMP_REAL, MULT_COMP_IMG, MULT_COMP_COMP, ABS_COMP, STOP};
const char *commands[] = {"read_comp", "print_comp", "add_comp", "sub_comp", "mult_comp_real", "mult_comp_img", "mult_comp_comp", "abs_comp", "stop"};
const char *variables[] = {"A", "B", "C", "D", "E", "F"};

/* remove all blanks in a line */
void remove_whites(char *line);

/* find command number in a line */
int find_command(char *line);

/* decode commands that use 2 variables which are add_comp, sub_comp and mult_comp_comp */
int decode_2_variables(char *line, char *var2);

/* decode commands that use 1 variable and 1 number which are mult_comp_real and mult_comp_img*/
int decode_mult(char *line, double *num1);

/* decode commands that use 1 variable and 2 numbers which is only read_comp */
int decode_read_comp(char *line, double *num1, double *num2);

void get_line(char line[]) {
    printf("Please enter a command:\n");
    if(fgets(line, LINE_LEN, stdin) == NULL) {
        printf("Reached EOF before stop command.\nThe program has finished.");
        exit(0);
    }
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
    if(c == STOP) {
        remove_whites(line);
        if(*line == '\0') {
            printf("Exiting program with stop command.\n");
            return 1;
        }
        else {
            printf("Extraneous text after end of command.\n");
            return 0;
        }
    }
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
    if(c == PRINT_COMP || c == ABS_COMP) {
        if(*line == '\0') return 1;
        else {
            printf("Extraneous text after end of command.\n");
            return 0;
        }
    }
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

int find_command(char *line) {
    int command_len, i = 0;
    for(i = 0; i < NUM_COMMANDS; i++) {
        command_len = strlen(commands[i]);
        if(!strncmp(line, commands[i], command_len)) return i;
    }
    return -1;
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