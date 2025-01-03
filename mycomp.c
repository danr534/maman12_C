#include "handle_input.h"

/* this program recieves input from user to make arithmetic operation on complex variables named A-F until recieving stop.
   if the command is not valid a corresponding message will apear and the line will be skipped, if it is valid the command will execute. 
*/
int main()
{
    complex variables[] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}; /* array to store the values of the complex variables A-F */
    char line[LINE_LEN]; /* array to store each line in the input */
    int command; /* command number of the current line */
    char var1 = '\0', var2 = '\0';  /* variable names (if exist) of the current line */
    double num1 = 0, num2 = 0; /* numbers parameters (if exist) of the current line */
    int is_valid; /* 1 if the line is a valid command and 0 otherwise */

    while(1) {
        get_line(line);
        is_valid = decode_line(line, &command, &var1, &var2, &num1, &num2);
        if(is_valid) {
            if(command == STOP) break;
            execute_line(variables, command, var1, var2, num1, num2);
        }
    }
    
	return 0;
}
