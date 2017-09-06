
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * a;

	if ((list->head) == NULL) 
	{
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	a = list->head;
	
	while (a != NULL) 
	{
		printf("%s",a->userName);

		a =a->next;

		if (a!=NULL) 
		{
			printf(", ");
		}
	}

	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, const char * userName, const char * password) {
	
	ListNode * a;
	a = (ListNode*)malloc(sizeof(ListNode));

	a->userName = strdup(userName);
	a->password = strdup(password);
	
	
	a->next = list->head;
	list->head = a;
}

void llist_add_room(LinkedList * list, const char * userName, int roomNumber) {
	
	ListNode * a;
	a =(ListNode*)malloc(sizeof(ListNode));

	a->userName =strdup(userName);
	a->roomNumber =roomNumber;
	
	
	a->next =list->head;
	list->head =a;
}

//
// Returns 1 if the value exists in the list.
// Returns 0 if the valur does not exist in the list. 
//
int llist_exists_name(LinkedList * list, const char * userName) {
	ListNode * b = list->head;
	
	while(b != NULL) 
	{
		if(strcmp(b->userName, userName) == 0)
		{
			return 1;
		}
		else
		{
			b = (b->next);
		}
	}

	return 0;
}

const char * llist_password(LinkedList * list, const char * userName) {    //return corresponding password
	ListNode * b = list->head;
	
	while(b != NULL) 
	{
		if(strcmp(b->userName,userName) == 0)
		{
			return (b->password);
		}
		else
		{
			b= b->next;
		}
	}
	return NULL;
}

int llist_roomNumber(LinkedList * list, const char * userName) {    //return corresponding roomNumber
	ListNode * a = list->head;
	
	while(a != NULL) 
	{
		if (strcmp(a->userName, userName)== 0)
		{
			return (a->roomNumber);
		}

		else
		{
			a= a->next;
		}
	}

	return -2;
}

void llist_sort(LinkedList * list) {
	ListNode * a = list->head;
	ListNode * b = a->next;
	
	const char * temporaryPass;
	const char * temporaryName;
	
    for (a = (list->head); a != NULL; a = a->next)
    {
		for (b = (a->next); b != NULL; b = (b->next))
		 {
			if (0 < strcmp(a->userName,b->userName)) 
			{
				temporaryName= strdup(b->userName);
				b->userName =strdup(a->userName);
				a->userName =strdup(temporaryName);

				temporaryPass =strdup(b->password);
				b->password= strdup(a->password);
				a->password= strdup(temporaryPass);
			}
		}
	}
}

void llist_sort_room(LinkedList * list) {
	ListNode * x = list->head;
	
	ListNode * y = x->next;
	
	const char * temporaryName;
	int temporaryRoom;
	for (x = list->head; x != NULL; x =(x->next)) 
	{
		for (y = (x->next); y != NULL; y =y->next) 
		{
			if (0 < strcmp(x->userName,y->userName)) 
			{
				temporaryName =strdup(y->userName);
				y->userName= strdup(x->userName);
				x->userName =strdup(temporaryName);

				temporaryRoom= y->roomNumber;
				y->roomNumber =x->roomNumber;
				x->roomNumber= temporaryRoom;
			}
		}
	}
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, const char * userName) {
	ListNode * a = list->head;
	
	if (strcmp(a->userName, userName) == 0) 
	{
		list->head=a->next;

		return 1;
	}
	while((a->next)!= NULL) 
	{
		if (strcmp(a->next->userName, userName)== 0) 
		{
			a->next = a->next->next;
	
			return 1;
		}

		else 
		{
			a = a->next;
		}
	}

	return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, const char * userName) {
	ListNode *b = list->head;
	
	int c;
	c = 0;

	while(b != NULL) 
	{
		if (c == ith) 
		{
			return 1;
		}

		b =b->next;
		c = c+1;
	}

	return 0;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode * a = list->head;
	
	int c;
	c = 0;

	while(a->next != NULL) 
	{
		a = a->next;
		c = (c+1);

		if (c == (ith - 1)) 
		{
			a->next = a->next->next;

			return 1;
		}
	}

	return 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	ListNode * a = list->head;
	
	int c;
	c= 0;

	while(a != NULL) {
		c = c + (10/10);
		a = a->next;
	}

	return c;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	FILE * fd;
	fd = fopen(file_name, "w+");

	ListNode * a = list->head;
	
	if(fd == NULL) 
	{
		return 0;
	}

	else 
	{
		while(a != NULL) 
		{
			fprintf(fd, "%s %s\n", a->userName, a->password);

			a = a->next;
		}

		fclose(fd);
	}

	return 0;
}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list){
	ListNode * a = list->head;
	
	ListNode *temporary;
	
	while(a != NULL) 
	{
		temporary = a;
		a = a->next;

		free(temporary);
	}

	list->head = NULL;
}

