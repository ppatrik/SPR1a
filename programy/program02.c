#include <stdio.h>

int main()
{
	int hodnota;
	printf("Zadaj číslo: ");
	scanf("%d", &hodnota);
	
	int i;
	for(i = 0; i <= hodnota; i++) {
		printf("%d\n", i);
	}	
	
	return 0;
}
