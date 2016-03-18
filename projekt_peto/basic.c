//
// Created by boss on 18.3.2016.
//

#include "basic.h"

void werror(const char *s, short code) {
    printf("CHYBA: %s \n\n", s);
    exit(code);
}

void strim(char *s) {
    s[strlen(s) - 1] = 0;
}