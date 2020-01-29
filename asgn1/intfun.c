/** ---------------------------------------------
 *
 * @file	intfun.c
 * @author	Nick McCollum
 * @version	2.0
 *
 * CS-201 - Asgn 1 - Integer Representation
 *
 * -------------------------------------------- */

#include "stdio.h"

const short MAX_BITS = 16;
const short MIN_NUM_TO_CONVERT = -3;
const short MAX_NUM_TO_CONVERT = 10;

/** ---------------------------------------------
 * 	
 * isBigEndian - Determines if the computer is
 *               big endian
 *
 * @return  Returns 1 if big endian, 0 otherwise
 *
 * -------------------------------------------- */
char isBigEndian();

/** ---------------------------------------------
* 	
* printAsBinary - Prints the binary representation
*				  of a decimal number
*
* @param 	numToPrint	The number to convert
*
* -------------------------------------------- */
void printAsBinary(short numToPrint);

/** ---------------------------------------------
* 	
* printSpaces - Adds spaces for formatted binary string
*
* @param 	numDigits	Number of digits to check
*
* -------------------------------------------- */
void printSpaces(short numDigits);

/** ---------------------------------------------
 * 	
 * rPrintAsBinary - Prints the binary representation
 *				    of a decimal number
 *
 * @param	numToPrint	The number to convert
 * @param	bitCount	Keeps count of bits
 *
 * -------------------------------------------- */
void rPrintAsBinary(short numToPrint, short* digitCount);

/** ---------------------------------------------
 * 	
 * printAsBinary - Wrapper for recursive rPrintBinary()
 *
 * @param 	numToPrint	The number to convert
 *
 * -------------------------------------------- */
void printAsBinaryRecursive(short numToPrint);

// ----------------------------------------------
int main() {

	printf("Author: Nick McCollum\n");

	// Print whether computer is big or little endian
	if (isBigEndian() == '1') {
		printf("Computer is big endian\n");
	}
	else {
		printf("Computer is little endian\n");
	}

	// Print the sizes of integer data types
	printf("\nsizeof(short) = %ld\n", sizeof(short));
	printf("sizeof(int) = %ld\n", sizeof(int));
	printf("sizeof(long) = %ld\n", sizeof(long));
	printf("sizeof(long long) = %ld\n", sizeof(long long));

	// Print table of integers in decimal, hex, and binary
	printf("\n%3s%5s%13s\n", "Dec", "Hex", "Binary");
	for (int x = MIN_NUM_TO_CONVERT; x <= MAX_NUM_TO_CONVERT; x++) {
		printf("%3d%#8.4hx  ", x, x);
//		printAsBinaryRecursive(x);
		printAsBinary(x);
		printf("\n");
	}

	return 1;
}

// ----------------------------------------------
char isBigEndian() {
	unsigned int hexNum = 0x1289;
	unsigned char* pHexNum;

	pHexNum = (unsigned char*) &hexNum;
	if (*pHexNum == 0x12) {
		return '1';
	}
	return '0';
}

// ----------------------------------------------
void printAsBinary(short numToPrint) {
	short binary[MAX_BITS];
	short bitPosition = MAX_BITS - 1;

	// Iterate through each bit and store in array
	while (bitPosition >= 0) {
		binary[bitPosition] = numToPrint & 1;
		numToPrint = numToPrint >> 1;
		bitPosition--;
	}

	// Iterate through the array and print values
	for (short i = 0; i < MAX_BITS; i++) {
		printSpaces(i);
		printf("%d", binary[i]);
	}
}

// ----------------------------------------------
void printSpaces(short numDigits) {
	if (numDigits % 8 == 0) {
		printf("  ");
	}
	else if (numDigits % 4 == 0) {
		printf(" ");
	}
}

// ----------------------------------------------
void rPrintAsBinary(short numToPrint, short* bitCount) {
	if (*bitCount == 0) {
		return;
	}

	// Call function for each bit to print
	*bitCount = *bitCount - 1;
	rPrintAsBinary(numToPrint >> 1, bitCount);

	// Print the binary digits
	*bitCount = *bitCount + 1;
	printf("%d", numToPrint & 1);
	printSpaces(*bitCount);
}

// ----------------------------------------------
void printAsBinaryRecursive(short numToPrint) {
	short bitCount = MAX_BITS;
	short* pBitCount = &bitCount;
	rPrintAsBinary(numToPrint, pBitCount);
}
