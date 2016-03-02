#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic.h"
#include "person.h"

#define PWD_FILE "password.secret"
#define INPUT_LENGTH 3 /* 3 pretoze ak by tam bol neaky skryty znak */

int main(int argc, char *argv[]) {
    while (1) {
        char volba[INPUT_LENGTH];
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        vypis("-------------------------------------");
        vypis("[1] Pridanie osoby");
        vypis("[2] Zobrazenie osoby");
        vypis("[3] Osdtránenie osoby");
        vypis("[Q] Ukončenie programu");
        vypis("-------------------------------------");
        printf("Zadaj voľbu: ");
        fgets(volba, INPUT_LENGTH, stdin);

        switch (volba[0]) {
            case '1':
                addPerson();
                break;
            case '2':


                break;
            case '3':

                break;
            case '0':
            case 'q':
            case 'Q':
                return EXIT_SUCCESS;
            default:
                vypis("Neznama volba!");
                break;
        }
    }
}
