#include "handle_input.h"

void get_line(char line[]) {
    if(fgets(line, LINE_LEN, stdin) == NULL) {
        printf("Reached EOF before stop command.\nThe program has finished.");
        exit(0);
    }
}