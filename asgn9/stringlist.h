/** ---------------------------------------------
*
* @file		stringlist.h
* @author	Nick McCollum
* @version	1.0
*
* CS-201 - Assignment 9: Dynamic Memory Allocation
* Linked list function definitions
*
* -------------------------------------------- */

struct node {
	char* data;
	struct node *next;
};

/** ---------------------------------------------
* 	
* insertNode - Insert a new node in correct order
*
* @param 	pHead		Pointer to list head
* @param 	strToAdd	The string to insert
*
* @return  				1 if inserted successfully,
*						0 otherwise
*
* -------------------------------------------- */
int insertNode(struct node** pHead, char* strToAdd);

/** ---------------------------------------------
* 	
* removeNode - Removes a node
*
* @param 	pHead		Pointer to list head
* @param 	strToRemove	The string to remove
*
* @return  				1 if removed successfully,
*						0 otherwise
*
* -------------------------------------------- */
int removeNode(struct node** pHead, char* strToRemove);

/** ---------------------------------------------
* 	
* printList - Prints all items space delimited
*
* @param 	pHead		Pointer to list head
*
* -------------------------------------------- */
void printList(struct node** pHead);

/** ---------------------------------------------
* 	
* deleteList - Removes all nodes
*
* @param 	pHead		Pointer to list head
*
* -------------------------------------------- */
void deleteList(struct node** pHead);
