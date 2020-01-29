/* ***********************************************************
 Name: doze.c
 Desc: demo program to demonstate sleep.  Used to start a "long" process
       so it can be put into the background and other stuff done while
       it executes.

	doze 10    (runs doze for 10 seconds)
	<cntrl z>  (to pause job, get control of console)
	bg	   (puts job in background)
	fg	   (to bring it back to foreground)

 Compile:   gcc -m32 -std=gnu99 -Wall -g -o doze doze.c 
************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	long waitTimeSec=0;
	char* endptr;

	if (argc < 2) {
		printf("usage: doze time_in_seconds\n");
		exit(2);
	}		

	waitTimeSec = strtol(argv[1], &endptr, 10);
	printf("waiting %ld seconds\n", waitTimeSec);
	sleep(waitTimeSec);

	printf("done\n");

	return 1;
}
