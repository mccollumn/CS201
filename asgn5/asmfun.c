/** ---------------------------------------------
*
* @file		asmfun.c
* @author	Nick McCollum
* @version	1.0
*
* CS-201 - Assignment 5: Embedded Assembly
*		   Using assembly, prints the volume of
*		   a sphere and your CPU Vendor ID
*
* -------------------------------------------- */
#include <stdio.h>

const double RADIUS = 4.5;
const int A = 3;
const int B = 10;
const int C = -3;

/** ---------------------------------------------
* 	
* sphereVolume - Calculates volume of a sphere
*				 using assembly
*
* @param 	radius	Sphere radius
*
* @return  	volume	Sphere volume
*
* -------------------------------------------- */
double sphereVolume(double radius);

/** ---------------------------------------------
* 	
* printCpuVendorID - Obtains and prints the CPU
*					 vendor ID using assembly
*
* -------------------------------------------- */
void printCpuVendorID();

/** ---------------------------------------------
* 	
* printRegister - Prints 4 hex values as ASCII
*				  characters
*
* @param 	reg		4 bytes in hex
*
* -------------------------------------------- */
void printRegister(int reg);

/** ---------------------------------------------
* 	
* quadraticFormula - Returns the + result of the
*					 quadratic formula
*
* @param 	a		Coefficient A
* @param 	b		Coefficient B
* @param 	c		Coefficient C
*
* @return  			The answer
*
* -------------------------------------------- */
double quadraticFormula(double a, double b, double c);

int main() {
	printf("Author: Nick McCollum\n\n");

	printf("Volume of a sphere with radius %2.1f:\n%f\n", RADIUS, sphereVolume(RADIUS));

	printCpuVendorID();

	printf("\n** Extra Credit **\n");
	printf("Quadratic equation (where a = %d, b = %d, c = %d):\n%f\n", A, B, C, quadraticFormula(A, B, C));

	return 1;
}

// ----------------------------------------------
double sphereVolume(double radius) {
	const int NUMERATOR = 4;
	const int DENOMINATOR = 3;
	double volume;

	asm(
		"	fldl	%[radius]	\n"
		"	fldl	%[radius]	\n"
		"	fldl	%[radius]	\n"
		"	fmulp				\n"
		"	fmulp				\n"
		"	fldpi				\n"
		"	fmulp				\n"
		"	fild	%[d]		\n"
		"	fild	%[n]		\n"
		"	fdivp				\n"
		"	fmulp				\n"
		"	fstpl	%[volume]	\n"

		:	[volume]	"=m"(volume)
		:	[radius]	"m" (radius),
			[n]			"m"	(NUMERATOR),
			[d]			"m" (DENOMINATOR)
		:
	);

	return volume;
}

// ----------------------------------------------
void printCpuVendorID() {
	int ebx, ecx, edx;
	
	asm(
		"	movl	$0, %%eax	\n"
		"	cpuid				\n"
		"	movl	%%ebx, %[b]	\n"
		"	movl	%%ecx, %[c]	\n"
		"	movl	%%edx, %[d]	\n"

		:	[b]		"=m"(ebx),
			[c]		"=m"(ecx),
			[d]		"=m"(edx)
		:
		:	"%eax", "%ebx", "%ecx", "%edx"
	);

	printf("\nCPU Vendor ID String:\n");
	printRegister(ebx);
	printRegister(edx);
	printRegister(ecx);
	printf("\n");
}

// ----------------------------------------------
void printRegister(int reg) {
	unsigned char* p;
	p = (unsigned char*) &reg;
	for (int i = 0; i < 4; i++) {
		printf("%c", *p);
		p++;
	}
}

// ----------------------------------------------
double quadraticFormula(double a, double b, double c) {
	double result;
	double four = 4;

	asm(
		"	fldl	%[a]		\n"
		"	fldl	%[c]		\n"
		"	fmulp				\n"
		"	fldl	%[four]		\n"	
		"	fmulp				\n"
		"	fldl	%[b]		\n"
		"	fldl	%[b]		\n"
		"	fmulp				\n"
		"	fsubp				\n"
		"	fsqrt				\n"
		"	fldl	%[b]		\n"
		"	fldz				\n"
		"	fsubp				\n"
		"	faddp				\n"
		"	fldl	%[a]		\n"
		"	fldl	%[a]		\n"
		"	faddp				\n"
		"	fdivrp				\n"
		"	fstpl	%[result]	\n"

		:	[result]	"=m"(result)
		:	[a]			"m" (a),
			[b]			"m" (b),
			[c]			"m"	(c),
			[four]		"m" (four)
		:
	);

	return result;
}
