#include <stdio.h>
#include <time.h>
// ANSI escape codes for text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char* get_time() {

    time_t currentTime;
    time(&currentTime);

    static char timeString[50]; // Adjust the size based on your needs
    struct tm *timeInfo;

    timeInfo = localtime(&currentTime);

    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);

    return timeString;
}


void info(const char *message) {

    printf("%s[INFO]%s::%s%s\n", ANSI_COLOR_GREEN, get_time(), message, ANSI_COLOR_RESET); 

}

void debug(const char *message) {

    printf("%s[DEBUG]%s::%s%s\n", ANSI_COLOR_YELLOW, get_time(), message, ANSI_COLOR_RESET); 

}

void error(const char *message) {

    printf("%s[ERROR]%s::%s%s\n", ANSI_COLOR_RED, get_time(), message, ANSI_COLOR_RESET); 

}