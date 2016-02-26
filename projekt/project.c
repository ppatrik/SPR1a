#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic.h"
#include "person.h"

#define PWD_FILE "password.secret"

int main(int argc, char *argv[])
{
    FILE *myFile = NULL;
    myFile = fopen(PWD_FILE, "r");
    if(myFile == NULL) {
        vypis("Subor s heslom neexistuje!");
        return EXIT_FAILURE;
    }
    char pwd[30], *pwd_save;
    pwd_save = pwd;
    char c;
    do {
        c = fgetc(myFile);
        *pwd_save = c;
        pwd_save++;
    } while(c != EOF);
    *--pwd_save = 0;

    fclose(myFile);

	char password[20];
	printf("Pre vstup do programu zadajte heslo: ");
	fgets(password, 19, stdin);
	
	if(strncmp(password, pwd, strlen(pwd)) != 0) {
		vypis("Jožo! Zas si zabudol heslo?\n\n");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
