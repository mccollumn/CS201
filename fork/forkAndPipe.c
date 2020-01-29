/* ***********************************************************
 Name: forkAndPipe.c
 Desc: demo program to show how to use a pipe for interprocess 
       communication.

 Compile:  gcc -m32 -Wall -g -o forkAndPipe forkAndPipe.c 
************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int fd[2];
	pid_t pid;	

	pipe(fd);
	pid = fork();

	//parent?
	if (pid>0) { 
		char buffer[100];
		int bytesRead;
		close(fd[1]); //close output end of pipe
		
		bytesRead = read(fd[0], buffer, sizeof(buffer)); //blocks
		printf("Received %d bytes: %s \n", bytesRead, buffer);
	}	

	// or child?
	else if (pid==0) { 
		close(fd[0]); //close input end of pipe
		char msg[] = "Child to Parent, send money.";
		//sleep(2); //children sleep alot.  Be the child.
		write(fd[1], msg, strlen(msg)+1 );
		exit(0);
	} 

	//or fork failure (highly unlikely).	
	else { 
		printf("fork failed! (weird)\n");
		exit(1);
	} 


	return 0;
}
