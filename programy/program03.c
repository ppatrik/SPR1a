#include <stdio.h>

int main()
{
	char retazec[20] = "Ahoj svet";
	// retazec je ukazovatel
	// retazec[nieco] uz je char
	
	retazec[2] = 0; // kazdy retazec konci nulovym znakom a teda bude vypisovat len Ah
	
	printf("%s \n", retazec);
	
	int x;
	for(x=0; x<20; x++) {
		printf("Char: %c, Ascii: %d \n", retazec[x], retazec[x]);
	}
	
	return 0;
}
