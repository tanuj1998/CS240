#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "review.h"

// Problem (1/4)
/******************************************************************************
 * TODO: Return a pointer to the first occurrence of the character 'c' in the 
 * string 's'. Return NULL if the character is not found.
 * 
 * Parameters: s -- string
 *             c -- search for this character in the string 's'
 *
 * Return: pointer to the first occurene of the character c in the string s
 *
 * Return Type: char pointer
 *****************************************************************************/
char *strchr(const char *s, int c) 
{
    // Write Your Code Here
    while(*s != '\0'){
    if(c == *s) {
    return (char *)s;
    }
    s++;
    }
    return NULL;
}

// Problem (2/4)
/******************************************************************************
 * TODO: Return the maximum element in the array
 * 
 * Parameters: array -- an integer array
 *             n -- number of elements in the array
 *
 * Return: the maximum element in the array
 *
 * Return Type: integer
 *****************************************************************************/
int max_array( int * array, int n )
{
    // Write Your Code Here
    int *a = array;
    int *b = a+n;
    int max = array[0];
    while(b > a)
    {
    if(*a > max){
    max = *a;
    }
    a++;
    }
    return max;
    
}

// Problem (3/4)
/******************************************************************************
 * TODO: Return the 'ith' bit in 'bitmap' (either 0 or 1)
 * 
 * Parameters: bitmap -- unsigned integer
 *             ith -- index of the bit to be returned
 *
 * Return: the largest element in the array 
 *
 * Return Type: integer
 *****************************************************************************/
int get_bit_at( unsigned int bitmap, int ith )
{
    // Write Your Code Here
    if(bitmap & (1<<ith)){
    return 1;
    }
    return 0;
}

// Problem (4/4)
/******************************************************************************
 * TODO: Read from the file and store the entries in to a single linked list.
 * Return the list. Use the function llist_add( List * list, int value ) to
 * add entries to the list. 
 *
 * The file format will be:
 * value\n
 * value\n
 * value\n
 * ...
 *
 * Parameters: filename -- the name of the file you will be reading from
 *
 * Return: a singled linked list which contains the values read from the file
 *
 * Return Type: pointer to a single linked list
 *****************************************************************************/
void llist_insert_last(List * list,int value);
List * llist_read( char * filename) 
{
    // Write Your Code Here
    List * list = (List*)malloc(sizeof(List));
    FILE *fd = fopen(filename,"r");
    if(fd == NULL){
    return NULL;
    }
    list->head = NULL;
    int c;
    while(fscanf(fd,"%d",&c) == 1){
    	llist_insert_last(list,c);
	}
    return list;
}

void llist_insert_last(List * list, int value)
	{
		ListNode * n = (ListNode*)malloc(sizeof(ListNode));
		ListNode * e = list->head;
		if(list->head == NULL)
			{
				n->value = value;
				list->head = n;
				n->next = NULL;
				return;
			}
		while(e->next != NULL){
			e = e->next;
		}

		n->value = value;
		e->next = n;
		n->next = NULL;
	}
	
