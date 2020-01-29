
/* ***********************************************************
 Name: memhog.c
 Desc: demo program to see how much memory a program can dynamically allocate.

 Compile and run as 32 bit vs 64 bit to see the difference
	gcc -m32 -std=gnu99 -Wall -g -o memhog memhog.c 
        gcc -std=gnu99 -Wall -g -o memhog memhog.c 
************************************************************* */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	long amt = 1024 * 1024 * 1024; //allocate it a GB at a time
	int count=0;
	void* mem;

	mem  = malloc(amt); //returns NULL if it fails (addr if successful)
	while ( mem ) {
		count++;
		printf("%dGB allocated!\n", count);
		mem  = malloc(amt); 		//ACK!! memory leak!!!
	}	

	return 1;
}

