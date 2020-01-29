/** ---------------------------------------------
*
* @file		floatfun.c
* @author	Nick McCollum
* @version	1.0
*
* CS-201 - Assignment 2a: Float Dissection
* Prints out the individual parts of a floating
* point value.
*
* -------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAX_BITS = 32;
const int SIGN_BITS = 1;
const int EXP_BITS = 8;
const int FRACTION_BITS = 23;

// Union used to convert int to float
union Fi {
	int i;
	float f;
};

/** ---------------------------------------------
* 	
* printBinary - Prints the binary representation
*				of a decimal number
*
* @param	num		Number to convert
* @param 	numBits	Number of bits to print
*
* -------------------------------------------- */
void printBinary(int num, int numBits);

/** ---------------------------------------------
* 	
* printSpaces - Adds spaces for formatting binary
*				string
*
* @param 	bitPosition	Position of current bit
*			being printed
*
* -------------------------------------------- */
void printSpaces(int bitPosition);

/** ---------------------------------------------
* 	
* getArg - Stores command line argument
*
* @param 	argc	Argument count
* @param 	argv	Array of argument values
* @param	num		Value provided on cmd line
*
* @return  			True if an arg was provided,
*					false otherwise
*
* -------------------------------------------- */
bool getArg(int argc, char* argv[], float* num);

/** ---------------------------------------------
* 	
* printOutput - Prints all output to console
*
* @param 	num		Number to print in output
*
* -------------------------------------------- */
void printOutput(union Fi num);

int main(int argc, char* argv[]) {
	union Fi num;

	if (!getArg(argc, argv, &num.f)) {
		return -1;
	}

	printOutput(num);

	return 1;
}

// ----------------------------------------------
void printBinary(int num, int numBits) {
	for (int bitPosition = numBits - 1; bitPosition >= 0; bitPosition--) {
		printf("%d", (num >> bitPosition) & 1);	
		printSpaces(bitPosition);
	}
	printf("\n");
}

// ----------------------------------------------
void printSpaces(int bitPosition) {
	if (bitPosition % 8 == 0) {
		printf("  ");
	}
	else if (bitPosition % 4 == 0) {
		printf(" ");
	}
}

// ----------------------------------------------
bool getArg(int argc, char* argv[], float* num) {
	// Verify one cmd line argument was provided
	if (argc != 2) {
		printf("Usage: %s float_value\n", argv[0]);
		return false;
	}

	// Get float value from cmd line
	*num = (float) atof(argv[1]);
	return true;
}

// ----------------------------------------------
void printOutput(union Fi num) {
	// Print name
	printf("Author: Nick McCollum\n\n");

	// Print decimal
	printf("%-12s %f\n", "Float val:", num.f);

	// Print hex
	printf("%-12s %#X\n", "In hex:", num.i);

	// Print binary
	printf("%-13s", "In binary:");
	printBinary(num.i, MAX_BITS);
	printf("\n");

	// Get sign, exp bits, and fraction
	int sign = (num.i >> (MAX_BITS - SIGN_BITS)) & 1;
	int expBits = (num.i >> FRACTION_BITS) & 0xFF;
	int fraction = num.i & 0x7FFFFF;

	// Print sign, exp bits, and fraction
	printf("%-12s %-10d %#-10X", "Sign:", sign, sign);
	printBinary(sign, SIGN_BITS);
	printf("%-12s %-10d %#-10X", "Exp bit:", expBits, expBits);
	printBinary(expBits, EXP_BITS);
	printf("%-12s %-10d %#-10X", "Fraction:", fraction, fraction);
	printBinary(fraction, FRACTION_BITS);
}

