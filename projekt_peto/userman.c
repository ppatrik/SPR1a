/*
 *   Vzorovy program pre demonstraciu IO v OS
 *   Autor:      Peter Pisarcik
 *   Vytvorene:  2016-03-16
 * 
 *   Kompilacia: gcc userman.c -o userman -std=gnu99 -Wall -pedantic
 * 
*/

#include "basic.h"
#include "person.h"


int main() {
    char v[MAX_INPUT];
    while (1) {
        printf("*********************************\n");
        printf(" MENU:\n");
        printf("---------------------------------\n");
        printf("1. Pridanie pouzivatela\n");
        printf("2. Vypis pouzivatelov\n");
        printf("3. Zobrazenie pouzivatela\n");
        printf("4. Uprava pouzivatela\n");
        printf("5. Odobranie pouzivatela\n");
        printf("0. Koniec programu\n");
        printf("---------------------------------\n");
        fgets(v, MAX_INPUT, stdin);
        int volba = atoi(v);
        switch (volba) {
            case 1:
                addPerson();
                break;
            case 2:
                listPersons();
                break;
            case 3:
                displayPerson();
                break;
            case 5:
                removePerson();
                break;
            case 4:
                editPerson();
                break;
            case 0:
                if (getUserCnt())
                    closeDB();
                return EXIT_SUCCESS;
            default:
                printf("Neznama volba.\n\n");
        }
    }
    return EXIT_SUCCESS;
}


/* End of file */
