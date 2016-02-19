#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
	
	char *retazce[3];
	
	int z;
	printf("Zadaj 3 retazcov:\n");
	for(z=0; z<3;z++) {
		retazce[z] = (char*)malloc(sizeof(char)*30);
		scanf("%s", retazce[z]);
	}
	
	for(z=3-1; z>=0;z--) {
		printf("Retazec %d: ", z);
		int i;
		for(i=strlen(retazce[z])-1; i >= 0; i--) {
			printf("%c", retazce[z][i]);
		}
		printf("\n");
		free(retazce[z]);
	}
	
	return 0;
	
}
