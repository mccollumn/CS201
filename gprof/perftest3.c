/* ***********************************************************
 Name: perftest.c
 Desc: demo program to test the performance of
        integer math vs floating point math.

 Compile 
	gcc -m32 -std=gnu99 -Wall -pg -g -o perftest3 perftest3.c

************************************************************* */

#include <stdio.h>

#define NUM_TIMES 100000000

double doubleMath(int numTimes) {
	double z1;
	double z2;
	double z3;
	double z4;
	double z5;
	double a=2.43;
	for (register int x=0; x<numTimes; x++) { 
		z1=x*a;
		z2=x*a;
		z3=x*a;
		z4=x*a;
		z5=x*a;
	}

	return z1+z2+z3+z4+z5;
}

int intMath(int numTimes) {
	int z1;
	int z2;
	int z3;
	int z4;
	int z5;
	int a=3;
	for (register int x=0; x<numTimes; x++){
		z1=x*a;
		z2=x*a;
		z3=x*a;
		z4=x*a;
		z5=x*a;
	}	
	return z1+z2+z3+z4+z5;
}
int emptyLoop(int numTimes) {
	for (register int x=0; x<numTimes; x++)
		; 
	return 1;
}

int main() {
	emptyLoop(NUM_TIMES);	
	intMath(NUM_TIMES);
	doubleMath(NUM_TIMES);

	printf("done\n");

	return 1;
}
