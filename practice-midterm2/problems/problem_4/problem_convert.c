#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX_DIGITS 32

// Problem (1/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting an integer
 *             base   -- the base of the number you are given
 * 
 * Return: The number as an integer
 *
 * Return Type: int
*****************************************************************************/
int toInteger(char * number, int base) {
// Write Your Code Here
	int len = strlen(number);
	int num = atoi(number);
	int a;
	int b;
	b = 0;

	int c;
	c = 0;
	
	int final;
	final= 0;
	
	if(base <= 10){
	for(a = 0; a < len; a = a+1)
	{
	 c = num % 10;
	 final += (c * (pow(base,a)));
	 num = num/10;
	 }
	 }
	 else{
	for(a = len - 1; a >= 0; a = a-1)
	{
	if(number[a] > 57)
	{
	final  += ((number[a] - 55) * (pow(base,b)));
	b = b+1;
	}
	else{
	final += ((number[a] - 48) * (pow(base,b)));
	b++;
	}
	}
	}
	return final;
}

// Problem (2/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting a string
 *             base   -- the base you are converting the numebr to
 * 
 * Return: The number as a string in base "base"
 *
 * Return Type: char *
*****************************************************************************/
char * toBase(int number, int base) {
	return NULL;
}
