/* ***********************************************************
 Name: fork2.c
 Desc: demo program to show another way to structure code that
	puts child code into it's own routine, and uses main for
	parent code (almost exclusviely)

 Compile:  gcc -std=gnu99 -Wall -g -o fork2 fork2.c 
************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// This routine contains all the processing for the child process.
// it doesn't return!  
void childRoutine() {
	printf("child (%d) is alive!\n", getpid());
	sleep(10);
	printf("child (%d) is ending.\n", getpid());
	exit(4);
}

// main is almost exclusively parent code.  
int main(int argc, char *argv[]) {
	pid_t 	pid;

	pid = fork();

	if (pid<0) {	
		printf("fork failed! (weird)\n");
		exit(-1);
	} else if (pid==0){
		childRoutine(); //doesn't return;
	} 

	//parent code
	pid_t childpid;
	int status;
	printf("parent (%d) is waiting for child (%d) to end.\n", getpid(), pid);
	childpid=wait(&status);	
	printf("child (%d) was reaped: %d\n", childpid, WEXITSTATUS(status));

	return 42;
}
