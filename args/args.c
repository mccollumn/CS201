
/* ***********************************************************
 Name: args.c
 Desc: demo program to show arguments passed to program.
 	  argc (argument count) = number of args passed
	  argv (argument values) = the value of each of those

 Compile: gcc -m32 -std=gnu99 -Wall -g -o args args.c
************************************************************* */

#include <stdio.h>
#include <stdlib.h>

/* int main(int argc, char* argv[]) { */
int main(int argc, char** argv) {

	//print arguments passed to program (as you'd use them)
	printf("argc: %d\n", argc);

	for(int x=0; x<argc; x++)
		printf("argv[%d]: %s\n", x, argv[x]);
	printf("\n");


	//print argv array of addresses and address they point to 
	// (i.e. details about how the argv array of pointers works)
	printf("addresses of argv entries and addresses they point to\n");
	for(int x=0; x<argc; x++)
		printf("&argv[%d]: 0x%x -> 0x%x\n", 
			x, 
			(unsigned int) &(argv[x]),
			(unsigned int) (argv[x])
		);

	printf("\n");

	return 1;
}

