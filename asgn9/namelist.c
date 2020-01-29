/** ---------------------------------------------
*
* @file		namelist.c
* @author	Nick McCollum
* @version	1.0
*
* CS-201 - Assignment 9: Dynamic Memory Allocation
*
* -------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringlist.h"

/** ---------------------------------------------
* 	
* getArgs - Stores cmd line args in an array
*
* @param 	argc	Argument count
* @param 	argv	Argument values
* @param 	args	Argument array 
*
* -------------------------------------------- */
void getArgs(int argc, char* argv[], char* args[]);

// ----------------------------------------------
int main(int argc, char* argv[]) {
	printf("Author: Nick McCollum\n\n");

	int numNames = argc - 1;
	char* args[numNames];
	getArgs(argc, argv, args);
	char* names[numNames];
	struct node* head = NULL;

	for (int i = 0; i < numNames; i++) {
		if (strncmp(args[i], "+", 1) == 0) {
			names[i] = malloc(strlen(args[i] + 1));
			strncpy(names[i], args[i] + 1, strlen(args[i]));
			insertNode(&head, names[i]);
			printf("Added %s\t\tList: ", names[i]);
			printList(&head);
			printf("\n");
		}
		else if (strncmp(args[i], "-", 1) == 0) {
			names[i] = malloc(strlen(args[i] + 1));
			strncpy(names[i], args[i] + 1, strlen(args[i]));
			removeNode(&head, names[i]);
			printf("Removed %s\t\tList: ", names[i]);
			printList(&head);
			printf("\n");
		}
	}	

	deleteList(&head);

	return 1;
}

// ----------------------------------------------
void getArgs(int argc, char* argv[], char* args[]) {
	if (argc == 1) {
		printf("Usage: %s <list of names>\n", argv[0]);
		exit(-1);
	}

	for (int i = 0; i < argc - 1; i++) {
		args[i] = malloc(sizeof(argv[i + 1]) + 1);
		strcpy(args[i], argv[i + 1]);
	}
}
