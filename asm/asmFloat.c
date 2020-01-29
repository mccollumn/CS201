//===================================================================
//
// Demo file.  Shows:
//	how to embed assembly into C code 
//	how to use floating point assembly instructions/registers
//
// Note: assembly code is NOT verified by compiler.  It just passed
//  it along to the assembler. 
//
//  By default, assembly must be in AT&T format.  
//
// Run in the debugger.  View floating point stack after each of the 
//   instructions in the asm using gdb command: info float
//
//===================================================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// doMath
double doMath(double a, double b, double c) {
	double result;
	double x=2.0;

	asm(
		"	fldl	%[x]		\n" 	
		"	fldl	%[a]		\n" 	
		"	fldl	%[b]		\n" 	
		"	fmulp			\n"	
		"	fldl	%[c]		\n" 	
		"	faddp			\n"
		"	fsubp			\n"
		"	fstpl	%[result]	\n" 
							//
		:	[result]	"=m"(result)	// outputs
		:	[a]      	"m" (a),	// inputs
			[b]      	"m" (b),	// inputs
			[c]      	"m" (c),	// inputs
			[x]	        "m" (x)		// inputs
		: 					// clobbers
	);

	return result;
}

int main(int argc, char **argv)
{
	double	a=3.0, b=4.0, c=5.0;
	double  result;

	result = doMath(a, b, c);
	
	printf("doMath(%.3f, %.3f, %.3f) = %.3f\n", a, b, c, result);
	
	return 0;
}
