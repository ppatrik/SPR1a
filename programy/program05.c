#include <stdio.h>

int main() {
	int x = 0xabcdefac;
	
	printf("X (hex) = %x \n", x);
	char *ch = (char*)&x;
	
	int y;
	for(y = 0; y < 4; y++) {
		printf("Znak: %x \n", ch[y]);
	}
	
	return 0;
}
