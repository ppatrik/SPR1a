#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *uprav(char slovo[]); // prototyp funkcie

char *uprav(char retazec[]) {
	int i = strlen(retazec);
	int x;
	for(x=(i-1); x>=0; x--) {
		if(retazec[x] < 32) {
			retazec[x] = 0;
		} else {
			break;
		}
	}
	return retazec;
}

int main(int argc, char **argv) {
	if(argc != 2) {
		printf("Zadaj pocet vstupov.\n");
		return -1;
	}
	
	int pocet = atoi(argv[1]);
	char buf[10][20];
	int i;
	for(i = 0; i < pocet; i++) {
		fgets(buf[i], 19, stdin);
	}
	for(i = 0; i < pocet; i++) {
		printf("Text: %s\n", uprav(buf[i]));
	}
	return 0;
}
