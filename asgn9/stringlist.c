/** ---------------------------------------------
 *
 * @file	stringlist.c
 * @author	Nick McCollum
 * @version	1.0
 *
 * CS-201 - Assignment 9: Dynamic Memory Allocation
 * Linked list function implementation
 *
 * -------------------------------------------- */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stringlist.h"

int insertNode(struct node** pHead, char* dataToAdd) {
	struct node* newNode = (struct node*) malloc(sizeof(struct node));
	newNode->next = NULL;
	newNode->data = malloc(sizeof(dataToAdd) + 1);
	strcpy(newNode->data, dataToAdd);

	// Empty list
	if (*pHead == NULL) {
		*pHead = newNode;
	}
	else {
		struct node* current = *pHead;
		struct node* previous = NULL;

		int found = 0;
		while (current != NULL) {
			if (strcmp(current->data, dataToAdd) >= 0) {
				found = 1;
				break;
			}
			else {
				previous = current;
				current = current->next;
			}
		}

		// Node is already in the list
		if (found == 1 && (strcmp(current->data, dataToAdd) == 0)) {
			return 0;
		}

		// Node belongs at the beginning
		if (current == *pHead) {
			newNode->next = *pHead;
			*pHead = newNode;
		}
		// Node belongs somewhere in the middle
		else {
			previous->next = newNode;
			newNode->next = current;
		}
	}
	return 1;
}

// ----------------------------------------------
int removeNode(struct node** pHead, char* dataToRemove) {
	// Empty list
	if (*pHead == NULL) {
		return 0;
	}
	else {
		struct node* current = *pHead;
		struct node* previous = NULL;

		while (current != NULL) {
			if (strcmp(current->data, dataToRemove) >= 0) {
				break;
			}
			else {
				previous = current;
				current = current->next;
			}
		}

		// Not in the list
		if (current == NULL) {
			return 0;
		}
		else {
			if (strcmp(current->data, dataToRemove) == 0) {
				// Node is at the beginning
				if (*pHead == current) {
					*pHead = current->next;
					free(current);
				}
				// Node is somewhere else
				else {
					previous->next = current->next;
					free(current);
				}
			}
		}
	}
	return 1;
}

// ----------------------------------------------
void printList(struct node** pHead) {
	struct node* current = *pHead;
	while (current != NULL) {
		printf("%s ", current->data);
		current = current->next;
	}
}

// ----------------------------------------------
void deleteList(struct node** pHead) {
	struct node* current;

	while (*pHead != NULL) {
		current = *pHead;
		*pHead = current->next;
		free(current);
	}
}
