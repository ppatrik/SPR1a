#include <stdio.h>
#include <stdlib.h>

#include "person.h"

int main(int argc, char *argv[])
{
	char password[20];
	printf("Pre vstup do programu zadajte heslo: ");
	fgets(password, 19, stdin);
	
	if(strncmp(password, "HESLO", 5) != 0) {
		printf("Jožo! Zas si zabudol heslo?\n\n");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
