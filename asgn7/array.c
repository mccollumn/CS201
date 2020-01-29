
/* ***********************************************************
 Name: array.c
 Desc: Initialzies, manipulates, and finds largest value in a
        2-d array.

	Students will analyze with gprof and improve code.

************************************************************* */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

static inline int largest(int x, int y) {
	if (x>y)
		return x;
	else
		return y;
}

int findLargest(int a[][SIZE]) {
	int largeNum=a[0][0];
//	char cmp;
//	int currentVal;
	for(register int x=0; x<SIZE; x++)
		for(register int y=0; y<SIZE; y++) {
			largeNum = largest(largeNum, a[x][y]);	

// Tried some stuff... 
//			currentVal = a[x][y];
//			if (a[x][y] > largeNum)	largeNum = a[x][y];	// Slighly faster than function call

//			largeNum = (largeNum > a[x][y]) ? largeNum : a[x][y];	// Same as previous

//			largeNum = (largeNum > currentVal) ? largeNum : currentVal;	// Using variable - about the same

//			char larger = largeNum < currentVal;
//			switch (larger) {
/*
			switch (largeNum < currentVal) {	// Fastest, but compile warning
				case 1: largeNum = currentVal;
			}
*/

//			if ((largeNum - currentVal) >> 31) largeNum = currentVal;
//			if ((largeNum - a[x][y]) >> 31) largeNum = a[x][y];

//			cmp = (largeNum - a[x][y]) >> 31;
//			if (cmp) largeNum = a[x][y];
		}
	return largeNum;
}

void doubleVals(int a[][SIZE]) {
	for(register int x=0; x<SIZE; x++)
		for(register int y=0; y<SIZE; y++)
//			a[x][y] = a[x][y]*2;	
//			a[x][y] *= 2;	// Same as original
			a[x][y] = a[x][y] << 1;
}

void initialize(int a[][SIZE]) {
	for(register int x=0; x<SIZE; x++)
		for(register int y=0; y<SIZE; y++)
			a[x][y] = x-y;	
}

int main() {
	static int a[SIZE][SIZE];
	int large;

	initialize(a);
	doubleVals(a);
	large = findLargest(a);	
	printf("%d\n",large); 

	return 0;
}
