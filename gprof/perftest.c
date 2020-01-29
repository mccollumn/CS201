/* ***********************************************************
 Name: perftest.c
 Desc: demo program to test the performance
	function call vs inline code

 Compile with profile switch:
	gcc -m32 -std=gnu99 -pg -o perftest_gprof perftest.c

 Run and create profile data (gprof.out)
	perftest_gprof 

 Run gprof
	gprof perftest_gprof gmon.out > analysis.txt

 View and analyize results
	vi analysis.txt

************************************************************* */

#include <stdio.h>

#define NUM_TIMES 1000000000

void swap(int* x, int*y) {
	int tmp=*x;
	*x=*y;
	*y=tmp;
}

int swap2(int numTimes) {
	int a=10;
	int b=20;
	for (int x=0; x<numTimes; x++)
		swap(&a,&b);
	return a*b;
}

int swap1(int numTimes) {
	int a=10;
	int b=20;
	int tmp;
	for (int x=0; x<numTimes; x++) {
		tmp=a;
		a=b;
		b=tmp;
	}

	return a*b;
}

int emptyLoop(int numTimes) {

	for (int x=0; x<numTimes; x++)
		; 
	return 1;
}

int main() {
	int z;
	int w;

	emptyLoop(NUM_TIMES);	
	z=swap1(NUM_TIMES);
	w=swap2(NUM_TIMES);

	printf("%d %d\n",z,w);

	return 1;
}

