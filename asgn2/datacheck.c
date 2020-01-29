/** ---------------------------------------------
*
* @file		datacheck.c
* @author	Nick McCollum
* @version	1.0
*
* CS-201 - Assignment 2b - Data Interpretation
*
* -------------------------------------------- */

#include <stdio.h>

/** ---------------------------------------------
* 	
* printBytes - Prints bytes in hex
*
* @param 	startAddress	Ptr to variable
* @param 	numBytes		Number of bytes to print
*
* -------------------------------------------- */
void printBytes(unsigned char* startAddress, int numBytes);

int main() {
	printf("Author: Nick McCollum\n\n");

	unsigned int numUInt = 3200253952;
	int numInt = -1094713344;
	unsigned short numUShort = 48832;
	short numShort = -16704;
	float numFloat = -0.375;

	unsigned char* ptr = (unsigned char*) &numUInt;
	printf("%-18s %-14u", "Unsigned int:", numUInt);
	printBytes(ptr, 4);

	ptr = (unsigned char*) &numInt;
	printf("%-18s %-14d", "Int:", numInt);
	printBytes(ptr, 4);

	ptr = (unsigned char*) &numUShort;
	printf("%-18s %-14d", "Unsigned short:", numUShort);
	printBytes(ptr, 2);

	ptr = (unsigned char*) &numShort;
	printf("%-18s %-14d", "Short:", numShort);
	printBytes(ptr, 2);

	ptr = (unsigned char*) &numFloat;
	printf("%-18s %-14f", "Float:", numFloat);
	printBytes(ptr, 4);

	return 1;
}

// ----------------------------------------------
void printBytes(unsigned char* startAddress, int numBytes) {
	printf("Bytes: ");
	for (int byte = 0; byte < numBytes; byte++) {
		printf("%#02x ", *startAddress++);
	}
	printf("\n");
}

