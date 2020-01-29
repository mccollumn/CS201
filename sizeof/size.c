#include <stdio.h>

//f(char* name)  // Functionally same as below
void f(char name[]) {
	printf("sizeof(name) = %d\n", (int) sizeof(name));
};

int main() {
	char name[10] = "Nick";
	printf("sizeof(name) = %d\n", (int) sizeof(name));
	f(name);

	return 1;
}
