#include "stdio.h"

int main() {

	unsigned int x = 0x12345678;
	unsigned char* xp;

	xp = (unsigned char*) &x;
	printf("%x\n", *xp);

	xp++;
	printf("%x\n", *xp);

	xp++;
	printf("%x\n", *xp);

	xp++;
	printf("%x\n", *xp);

	return 1;
}
