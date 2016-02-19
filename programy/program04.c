#include <stdio.h>

int main() {
	char input;
	printf("Zadajte písmeno A-D: ");
	scanf("%c", &input);
	printf("Zadali ste %c\n", input);
	switch(input) {
		case 'a':
		case 'A':
			printf("Meno bude Andrea");
			break;
		case 'b':
		case 'B':
			printf("Meno bude Barbora");
			break;
		case 'c':
		case 'C':
			printf("Meno bude Cecil");
			break;
		case 'd':
		case 'D':
			printf("Meno bude Daniel");
			break;
		default:
			printf("Zadali ste hovadinu");
		
	}
	return 0;
}
