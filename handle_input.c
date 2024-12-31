#include "handle_input.h"

#define NUM_COMMANDS 9
#define NUM_VARIABLES 6

/* numbers to identify the command names */
enum names {READ_COMP, PRINT_COMP, ADD_COMP, SUB_COMP, MULT_COMP_REAL, MULT_COMP_IMG, MULT_COMP_COMP, ABS_COMP, STOP};
const char *commands[] = {"read_comp", "print_comp", "add_comp", "sub_comp", "mult_comp_real", "mult_comp_img", "mult_comp_comp", "abs_comp", "stop"};
const char *variables[] = {"A", "B", "C", "D", "E", "F"};

int count_commas(char *word);
int decode_2_variables(char *word, char *y);
int decode_mult(char *word, double *z);
int decode_read_comp(char *word, double *z, double *w);

void get_line(char line[]) {
    printf("Please enter a command:\n");
    if(fgets(line, LINE_LEN, stdin) == NULL) {
        printf("Reached EOF before stop command.\nThe program has finished.");
        exit(0);
    }
}

int decode_line(char line[], int *command, char *x, char *y, double *z, double *w) {
    int c;
    /* get the first word seperated by space or tab */
    char *word;
    word = strtok(line, " \t\n");

    /* check if the line is empty */
    if(word == NULL) return 0;

    /* check if there is an illegal comma */
    if(word[strlen(word) - 1] == ',') {
        printf("Illegal comma.\n");
        return 0;
    }

    /* check if the word is a valid command */
    for(c = 0; c < NUM_COMMANDS; c++) {
        if(!strcmp(word, commands[c])) break; /* if the word is equal to a string in commands then c is the index of the string */
    }
    
    /* if the word is not in commands print the following error */
    if(c == NUM_COMMANDS) {
        printf("Undefined command name.\n");
        return 0;
    }

    *command = c; /* save the command number */

    /* get the first parameter */
    word = strtok(NULL, " \t\n");

    /* check if the command is stop */
    if(c == STOP) {
        if(word == NULL) {
            printf("Exiting program with stop command.\n");
            return 1;
        }
        else {
            printf("Extraneous text after end of command.\n");
            return 0;
        }
    }

    /* check if the word is a valid variable */
    if(word == NULL) {
        printf("Missing parameter.\n");
        return 0;
    }
    
    if(*word < 'A' || *word > 'F') {
        printf("Undefined complex variable.\n");
        return 0;
    }

    if((c == PRINT_COMP || c == ABS_COMP) && strlen(word) > 1) {
        printf("Extraneous text after end of command\n");
        return 0;
    }

    if(c != PRINT_COMP && c != ABS_COMP && strlen(word) == 1) {
        printf("Missing comma.\n");
        return 0;
    }

    if(count_commas(word) > 1) {
        printf("Multiple consecutive commas\n");
        return 0;
    }

    if(strlen(word) > 2 || (strlen(word) == 2 && count_commas(word) == 0)) {
        printf("Undefined complex variable.\n");
        return 0;
    }

    *x = *word;
    
    /* get the second parameter */
    word = strtok(NULL, " \t\n");

    /* check if the command uses only 1 variable */
    if(c == PRINT_COMP || c == ABS_COMP) {
        if(word == NULL) return 1;
        else {
            printf("Extraneous text after end of command.\n");
            return 0;
        }
    }

    if(c == ADD_COMP || c == SUB_COMP || c == MULT_COMP_COMP) return decode_2_variables(word, y);
    else if(c == MULT_COMP_REAL || c == MULT_COMP_IMG) return decode_mult(word, z);
    else return decode_read_comp(word, z, w);

    return 1;
}

int count_commas(char *word) {
    int count = 0;
    int i;
    for(i = 0; i < strlen(word); i++) {
        if(word[i] == ',') count++;
    }
    return count;
}

int decode_2_variables(char *word, char *y) {
    char *rest_of_line;

    if (word == NULL) {
        printf("Missing parameter\n.");
        return 0;
    }

    if(*word < 'A' || *word > 'F') {
        printf("Undefined complex variable.\n");
        return 0;
    }

    rest_of_line = strtok(NULL, "\n");

    if(strlen(word) > 1 || rest_of_line != NULL) {
        printf("Extraneous text after end of command\n");
        return 0;
    }

    *y = *word;
    return 1;
}

int decode_mult(char *word, double *z) {
    char *endPtr;
    double value;
    char *rest_of_line;

    if(word == NULL) {
        printf("Missing parameter\n.");
        return 0;
    }

    value = strtod(word, &endPtr);
    if(*endPtr) {
        printf("Invalid parameter - not a number\n");
        return 0;
    }

    rest_of_line = strtok(NULL, "\n");
    if(rest_of_line != NULL) {
        printf("Extraneous text after end of command\n");
        return 0;
    }

    *z = value;
    return 1;
}

int decode_read_comp(char *word, double *z, double *w) {
    char *endPtr;
    double value;

    if(word == NULL) {
        printf("Missing parameter\n.");
        return 0;
    }

    value = strtod(word, &endPtr);

    if(*endPtr != ',') {
        printf("Missing comma.\n");
        return 0;
    }
    /* check for mult_comp_real A , 3... */
    *z = value;


}
