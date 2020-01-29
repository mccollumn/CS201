#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char* str = "String";
	printf("%s\n", str);

//	char* result;
//	result = (char*) malloc (7);

	char result[7];
	char* p = str;

//	char letter[1];

	for (int i = 0; i < 6; i++) {
	printf("Int: %x\n", (int)*p);
	printf("Char: %c\n", *p);

	result[i] = *p;
//	letter = (char*)*p;
//	strcat(result, letter);

	int flip = (int)*p ^ 0xff;
	printf("Flip int: %x\n", flip);
	printf("Flip char: %c\n", (char)flip);

	
	p++;
	}

	printf("%s\n", result);

	return 1;
}
