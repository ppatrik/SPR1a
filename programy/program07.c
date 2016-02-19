#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
	
	char retazce[10][30];
	int z;
	printf("Zadaj 10 retazcov:\n");
	for(z=0; z<10;z++) {
		scanf("%s", retazce[z]);
	}
	
	for(z=10-1; z>=0;z--) {
		printf("Retazec %d: ", z);
		int i;
		for(i=strlen(retazce[z])-1; i >= 0; i--) {
			printf("%c", retazce[z][i]);
		}
		printf("\n");
	}
	
	return 0;
	
}
