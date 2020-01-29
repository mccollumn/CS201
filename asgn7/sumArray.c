
/* ***********************************************************
 Name: sumArray.c
 Desc: Assignment 8 - Sums up array elements numerous times

	Students will modify sumArray routine to improve 
	performance.

 Compile 
	gcc -m32 -std=gnu99 -Wall -g sumArray.c -o sumArray

 Time execution:
	time sumArray

************************************************************* */


#include <stdio.h>
#include <stdlib.h>

#define NUM_TIMES 50000
#define ARR_SIZE  100000

// Any size array can be provided
static inline double sumArray(double array[]) {
	const unsigned char blockSize = 10;
	register double* p = array;
	double* endArray = &array[ARR_SIZE];		// End of the array
	double* end = endArray - (blockSize - 1);	// End of the last block
	register double sum = 0;

	// Sum a block of ten numbers at a time
	for (; p < end; p += blockSize)
		sum += *p + *(p+1) + *(p+2) + *(p+3) + *(p+4) + *(p+5) + *(p+6) + *(p+7) + *(p+8) + *(p+9);

	// Sum any remaining numbers, if the array size is not divisible by 10
	for (;p < endArray; p++)
		sum += *p;

	return sum;
}

int main() {
	//print your name
	printf("Nick McCollum\n");

	//create and initialize array
	double *array = calloc(ARR_SIZE, sizeof(double));

	array[0]=5;
	array[ARR_SIZE-1]=4;

	//sum up array elements a bunch of times (once is too fast)
	double sum;
	for(int n=0; n<NUM_TIMES; n++) {
		sum=sumArray(array);
	}

	/* print out total to verfiy we processed all entries */
	printf("sum: %lf\n", sum);

	return 1;
}
