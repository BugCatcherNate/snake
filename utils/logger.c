#include <stdio.h>
#include <time.h>
// ANSI escape codes for text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"



void info(const char *message) {
time_t currentTime;
    time(&currentTime);

    printf("%s[INFO]%s:%s%s\n", ANSI_COLOR_GREEN, ctime(&currentTime), message, ANSI_COLOR_RESET); 

}

void debug(const char *message) {
    time_t currentTime;
    time(&currentTime);


    printf("%s[DEBUG]%s:%s%s\n", ANSI_COLOR_YELLOW, ctime(&currentTime), message, ANSI_COLOR_RESET); 

}
