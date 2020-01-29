/* ***********************************************************
 Name: sig.c
 Desc: demo program to demonstate signal handling. 
	note: uses pause, which can have issues in certain circumstances.

   Do use the following:	
	sig &	 - runs sig in background  
	ps       - shows process id's of running processes
	kill -s USR1 [process id of sig process)
	kill -s USR2 [process id of sig process)
	kill [process id of sig process)

 Compile 
	gcc -m32 -std=gnu99 -Wall -g -o sig sig.c 
************************************************************* */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>



void sigHandler2( int sig) {
	printf("BOOOO!!!!!\n");
	fflush(stdout);
}

void sigHandler( int sig) {
	printf("signal: %d recieved\n", sig);
	fflush(stdout);
	signal(SIGUSR1, sigHandler2);
}

void sigHandlerTerm( int sig) {
	printf("Termination (%d) signal recieved!  Being ignored.\n",sig);
	fflush(stdout);
}

int main(int argc, char *argv[]) {

	//set up signal handlers. If these signals are received, the
	//handler is called
	signal(SIGUSR1, sigHandler);
	signal(SIGUSR2, sigHandler);
	signal(SIGTERM, sigHandlerTerm);

	
	//wait for a signal to arrive	
	//	while(1) //uncomment this to process multiple signals
	//	pause();

	/* this block will show signals interrupt normal processing */
		
	while (1) {
		printf("x");
		fflush(stdout);
		sleep(2); //2 seconds
	} 

	printf("done\n");

	return 1;
}
