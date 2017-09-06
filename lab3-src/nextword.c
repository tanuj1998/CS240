
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
        int x = 0;
  	int c;
	while((c = fgetc(fd))!= -1){
	if(c == ' ' || c=='\n' || c== '\t' || c=='\r')
	{
	if(wordLength == 0){
		continue;
	}
	word[wordLength] = '\0';
	wordLength = 0;
	return word;
	exit(1);
	}
        else {
        x = 1; 
	word[wordLength] = c;
	wordLength++;
	}
      }
      if(x == 1)
      {
       word[wordLength] = '\0';
       return word;
      }
      else {
     return NULL;
     }

	
	// While it is not EOF read char
		// While it is not EOF and it is a non-space char
		// store character in word.
		// if char is not in word return word so far.
		//
	// Return null if there are no more words

}
