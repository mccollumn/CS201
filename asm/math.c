#include <stdio.h>

void math() {
	asm("movl $0xe,-0xc(%ebp);");
	asm("movl $0xa,-0x8(%ebp);");
	asm("mov -0xc(%ebp),%eax;");

}

int main() {
	math();
	return 1;
}
