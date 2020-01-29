/* ***********************************************************
 Name: perftest2.c
 Desc: demo program to test the performance
	pointer vs array index notation
 
 Compile with profile switch:
	gcc -m32 -std=gnu99 -pg -o perftest2_gprof perftest2.c

 Run and create profile data (gprof.out)
	perftest2_gprof 

 Run gprof
	grpof perftest2_gprof gmon.out > analysis.txt

 View and analyize results
	vi analysis.txt

************************************************************* */

#include <stdio.h>

#define SIZE	  100000000
#define NUM_TIMES 10

int initializeA(int a[], int size) {
	for (int x=0; x<size; x++) {
		a[x] = 42;
	}

	return 1; 
}

int initializeP(int a[], int size) {
	int* end=&a[size];
	for (int* ptr=a; ptr<end; ptr++) {
		*ptr = 42;
	}

	return 1; 
}

int main() {
	static int a[SIZE];

	for(int x=0; x<NUM_TIMES; x++) {
		initializeP(a, SIZE);
		initializeA(a, SIZE);
	}

	printf("done.\n");

	return 1;
}
