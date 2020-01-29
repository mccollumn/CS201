/** ---------------------------------------------
*
* @file		forkfun.c
* @author	Nick McCollum
* @version	1.0
*
* CS-201 - Assigment 8: Processes
*
* -------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

/** ---------------------------------------------
* 	
* getForkCount - Reads fork count from cmd line
*
* @param	argc	Argument count
* @param 	argv	Argument values
*
* @return  			Fork count
*
* -------------------------------------------- */
int getForkCount(int argc, char* argv[]);

/** ---------------------------------------------
* 	
* sigusr1Handler - Handles USR1 signal and passes
*				   the signal to all child PIDs
*
* @param 	sig		Signal
*
* -------------------------------------------- */
void sigusr1Handler(int sig);

/** ---------------------------------------------
* 	
* sigtermHandler - Handles TERM signal, killing
*				   parent and all child PIDs
*
* @param 	sig		Signal
*
* -------------------------------------------- */
void sigtermHandler(int sig);

/** ---------------------------------------------
* 	
* sigusr1ChildHandler - Handles USR1 signal for
*					    child PIDs
*
* @param 	sig		Signal
*
* -------------------------------------------- */
void sigusr1ChildHandler(int sig);

/** ---------------------------------------------
* 	
* childRoutine - Performs child actions then exits
*
* @param 	sleepTime	Seconds to sleep
*
* -------------------------------------------- */
void childRoutine(int sleepTime);

/** ---------------------------------------------
* 	
* reapChildren - Reaps all children and prints
*				 sum of signals received
*
* @param 	forkCount	Number of child PIDs
*
* -------------------------------------------- */
void reapChildren(int forkCount);

/** ---------------------------------------------
* 	
* spawnChildren - Spawns child processes
*
* @param 	forkCount	Number of child PIDs
*
* -------------------------------------------- */
void spawnChildren(int forkCount);

const int MIN_SLEEP = 30;
const int MAX_SLEEP = 60;

// Globals that need to be accessible by signal handlers
pid_t* childPids;
int numSignals = 0;

// ----------------------------------------------
int main(int argc, char* argv[]) {
	int forkCount = getForkCount(argc, argv);
	childPids = calloc(forkCount, sizeof(pid_t));	

	printf("PARENT: process ID is %d\n", getpid());
	printf("PARENT: forking %d processes\n\n", forkCount);

	srand(time(0));

	spawnChildren(forkCount);

	// Parent signal handlers
	signal(SIGUSR1, sigusr1Handler);
	signal(SIGTERM, sigtermHandler);

	// Ensure enough time for child routines to kick off before continuing
	usleep(500);
	printf("PARENT: waiting for children to end.\n\n");
	
	reapChildren(forkCount);

	return 1;
}

// ----------------------------------------------
int getForkCount(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: %s Num forks\n", argv[0]);
		exit(-1);
	}

	int num = atoi(argv[1]);
	if (num < 1)
		return 1;
	else if (num > 4)
		return 4;
	return num;
}

// ----------------------------------------------
void sigusr1Handler(int sig) {
	printf("PARENT: SIGUSR1 signal received!\n");
	kill(-childPids[0], SIGUSR1);
}

// ----------------------------------------------
void sigtermHandler(int sig) {
	kill(-childPids[0], SIGKILL);
	raise(SIGKILL);	
}

// ----------------------------------------------
void sigusr1ChildHandler(int sig) {
	printf("CHILD: SIGUSR1 signal received!\n");
	numSignals++;
}

// ----------------------------------------------
void childRoutine(int sleepTime) {
	printf("CHILD %d is alive! (Sleeping for %d seconds)\n\n", getpid(), sleepTime);
	fflush(stdout);

	signal(SIGUSR1, sigusr1ChildHandler);

	int remainingTime = sleep(sleepTime);
	while (remainingTime > 0) {
		remainingTime = sleep(remainingTime);
	}

	exit(numSignals);
}

// ----------------------------------------------
void reapChildren(int forkCount) {
	int childStatus;
	for (int i = 0; i < forkCount; i++) {
		wait(&childStatus);
		if (WIFEXITED(childStatus)) {
			numSignals += WEXITSTATUS(childStatus);
		}
	}
	printf("\nTotal child signals: %d\n", numSignals);
}

// ----------------------------------------------
void spawnChildren(int forkCount) {
	for (int i = 0; i < forkCount; i++) {
		int sleepTime = (rand() % (MAX_SLEEP - MIN_SLEEP + 1)) + MIN_SLEEP;

		pid_t pid = fork();
		childPids[i] = pid;

		// Set PID group for easier child signal handling
		setpgid(pid, childPids[0]);

		if (pid < 0) {
			printf("Could not create new process\n");
		}
		else if (pid == 0) {
			childRoutine(sleepTime);
		}
	}
}
