#include <stdio.h>

int main() {
	char x = 0xf0;
	unsigned char z = 0xf0;

	printf("x=%hhx %d\n", x, x);
	printf("z=%x %d\n", z, z);

	printf("\nShifting right one bit...\n");
	x = x >> 1;
	z = z >> 1;

	printf("x=%hhx %d\n", x, x);
	printf("z=%x %d\n", z, z);

	return 1;
}

