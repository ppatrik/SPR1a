#include <stdio.h>

int main (int argc, char *argv[]) {
	int z;
	for(z = 0; z<argc; z++) {
		printf("Parameter %d: %s\n", z, argv[z]);
	}
	
	char ch1[] = "ahoj svet";
	char ch2[] = "nazdar";
	char **pole_retazcov;
	pole_retazcov[0] = ch1
	pole_retazcov[1] = ch2
	return 0;
}
