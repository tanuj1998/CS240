/*
 *  CS 24000 First mid-semester exam.
 *   Problem #22
 *
 *  int isPalindrome(char * str)
 *
 *  Arguments:
 *		char * str -- a pointer to a string
 *
 *  Return:
 *		1 if the string is a palindrome, 0 otherwise
 *		
 *  Description:
 *		Given a string of input, return 1 if str is a palindrome, 0 otherwise. A 
 * 		palindrome is a word, phrase, or sequence that reads the same backward as
 *		forward. The function ignores all white spaces (space, tab, newline or 
 * 		carriage return). For example, "madam" and "nurses run" are palindromes.
 */

 /* ======================== Start your edits here =========================== */
 
 /*
  *  NOTE NOTE NOTE NOTE NOTE
  *  You are not allowed to add any other libraries or library includes in addition
  *   to <stdlib.h> other than <math.h> (if you believe you need it).
  */

 #include <stdlib.h>
 /* 
  * Complete the function below for the exam
  */

int isPalindrome(char * str)
 {  int i;
    int j;
    int length = 0;
    for(i = 0; i <= length/2; i++){
    for(j = 0; j <= length - 1;j--)
    {
    if(i != j){
    return 1;
    }
    else{
    return 0;
    }
    }
    }
   return 1;
 }
  
 /* ======================== End your edits here =========================== */

 /*
 ************************************************************************
  *  Do NOT change any of the lines between here and the end of the file!
 ************************************************************************
  */

#include <stdio.h>
#include <assert.h>

char *Usage = "Usage: %s <string>\n";

int main(int argc, char *argv[])
{
	unsigned int result;
		
	if (argc != 2) 
	{
		fprintf(stderr, Usage, argv[0]);
		exit(1);
	}
	
	result = isPalindrome(argv[1]);

	printf("%s %s a palindrome\n", argv[1], (result == 1) ? "is" : "is not");
	
	return 0;
}
