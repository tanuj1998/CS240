
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

	if (list->head == NULL) 
	{
		printf("{EMPTY}\n");
		return;
	}
        printf("{");

	a = list->head;
	while (a != NULL) 
	{
		printf("%d", a->value);
		a = a->next;
		if (a != NULL) 
		{
			printf(", ");
		}
	}

	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode *a = (ListNode *) malloc(sizeof(ListNode));
	a->value = value;
	// Add at the beginning of the list
	a->next = list->head;
	list->head = a;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
	LIstNode *b = list->head;
	while(b!=NULL){
	if(b->value == value){
            return 1;
	}

	b = b->next;
	}
        return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {

	ListNode *a = list->head;
	LIstNode *b = a->next;

	while(b!=NULL){
	if(b->value == value){
	a->next = b->next;

	return 1;
	}

	b = b->next;
	a = a->next;
	}

	return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	
	ListNode *a = list->head;
	int b = 0;
	
	while(a!=NULL){
	if(b == ith){
	
        *value = a->value;
        return 1;
	}

	b++;
	a = a->next;
	}

	return 0;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode * a;
	a = list->head;
	ListNode * b;
	b = a->next;
	int x = 1;

	while(b!=NULL){
	if(x == ith){
	
        a->next = b->next;
        return 1;
	}

	a = a->next;
        b = b->next;
	x++;
	}

	return 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	
	ListNode * x;
	x = list->head;

	int a = 0;
	
	while(x!= NULL){

	a++;
	x = x->next;
	}
        return a;
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
	ListNode * a;
	a = list->head;
	FILE * fd = fopen(file_name,"w+");
	
	if(fd==NULL){

	return 0;
	}

	while(a!=NULL){
	fprintf(fd,"%d\n",a->value);
        a = a->next;
	}

	fclose(fd);

	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	
	FILE * fd = fopen(file_name,"r");
	
        if(fd==NULL){
	return 0;
	}

	int a;
	list->head = NULL;

	while(fscanf(fd,"%d", &a) == 1){
	ListNode *b = (ListNode*)malloc(sizeof(ListNode));

	b->value = a;
	b->next = list->head;
	list->head = b;

	}

	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//

void llist_sort(LinkedList * list, int ascending) {
   int c;

   ListNode * a = list->head;
   ListNode * b = a->next;
   

   if(ascending == 0){
   for(a=list->head; a!=NULL; a=a->next){
      for(b=a->next; b!=NULL; b=b->next){

         if((b->value)>(a->value)){
         c = b->value;
         b->value = a->value;
         a->value = c;
         }
       }
      }
     }

     else if(ascending == 1){
          for(a=list->head; a!=NULL; a=a->next){
            for(b=a->next; b!=NULL; b=b->next){
               if((b->value)<( a->value)){
               c = b->value;
               b->value = a->value;
               a->value = c;
             }
          }
        }
     }
     
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
	ListNode * a;

	a = list->head;

	if(a==NULL)
	{

	return 0;

	}
	*value = a->value;
	list->head = list->head->next;
	free(a);

	return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
      ListNode * b;
      b = list->head;

      if(b==NULL)
      {
      return 0;

      }

      while(b->next->next!=NULL)
      {
      b = b->next;

      }

      *value = b->next->value;
      free(b->next);
      b->next = NULL;

      return 1;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
      llist_add(list, value);
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
     ListNode * a;
     a = (ListNode*)malloc(sizeof(ListNode));

     a->value = value;
     a->next = NULL;

     ListNode * b;
     b = list->head;
     if(b==NULL)
     {
     list->head = a;
     return;
     }

     while(b->next!=NULL)
     {
     b  = b->next;
    }
    b->next = a;
}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
  list->head = NULL;
}

