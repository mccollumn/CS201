

#include <stdio.h>

int domath(int x);

int main() {
	int z=12;

	z=domath(5);

	return z;
}

int domath(int x) {
	int y=7;

	int z;

	z=x+4;
	z*=2;

	z=z-y;

	return y;
}
