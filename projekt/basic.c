#include "basic.h"

void vypis(const char *s) {
    printf("Vypis: %s\n", s);
}


void werror(const char *s, int code) {
    vypis(s);
    exit(code);
}

char *rtrim(char retazec[]) {

    int i = strlen(retazec);
    int j;
    for (j = (i - 1); j >= 0; j--) {
        if (retazec[j] < 32) {
            retazec[j] = 0;
        } else {
            break;
        }
    }
    return retazec;
}