#include <stdio.h>
// ANSI escape codes for text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"



void log(const char *message) {
    printf("%s%s%s", ANSI_COLOR_GREEN, message, ANSI_COLOR_RESET); 

}

