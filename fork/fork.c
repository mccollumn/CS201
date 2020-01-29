/* ***********************************************************
 Name: fork.c
 Desc: demo program to show how to fork a process and reap the child process.

 Compile:  gcc -std=gnu99 -Wall -g -o fork fork.c 
************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t 	pid;

	pid = fork();
	printf("\n\n"); fflush(stdout);
	
	if (pid>0) {	
		// parent
		pid_t childpid;
		int status;
		printf("Parent: process has forked!\n");
		printf("Parent: parent (%d) is waiting for child (%d) to end.\n",
			 getpid(), pid);
		sleep(20);
		childpid=wait(&status);	
		printf("Parent: child (%d) was reaped: %d\n", 
			childpid, WEXITSTATUS(status));
	} else if (pid==0){
		// child
		printf("Child: child (%d) is alive!\n", getpid());
		sleep(5);
		printf("Child: child (%d) is ending.\n", getpid());
	}
	else
		printf("fork failed! (weird)\n");

	return 23;
}
