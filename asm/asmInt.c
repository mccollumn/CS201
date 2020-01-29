//===================================================================
//
// Demo file.  Shows:
//	how to embed assembly into code
//
// Note: assembly code is NOT verified by compiler.  It just passed
//  it along to the assembler. 
//
//  By default, assembly must be in AT&T format.  
//
// Run in the debugger.  View register values after each of the 
//   instructions in the asm using gdb command: info registers 
//
//===================================================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// doMath
int doMath() {
	int a=4;
	int b=5;
	int sum;

	asm(
		"	movl	%[x], %%ebx	\n" 	
		"	movl	%[y], %%eax	\n" 	
		"	addl	%%eax, %%ebx	\n" 	
		"	movl	%%ebx, %[sum]	\n"
							// 	
		:	[sum]		"=m"(sum)	// outputs
		:	[x]    		"m" (a),	// inputs
			[y]    		"m" (b)		// inputs
		:	"%eax", "%ebx"			// clobbers
	);

	return sum;
}

int main(int argc, char **argv)
{
	int z = doMath();
	
	printf("doMath() = %d\n", z);
	
	return 0;
}



