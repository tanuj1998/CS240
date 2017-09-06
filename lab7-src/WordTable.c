#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define isaletter(ch) ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))
#include "WordTable.h"

// Initializes a word table
void wtable_init(WordTable * wtable)
{       
        // Allocate and initialize space for the table
        wtable->nWords = 0;
        wtable->maxWords = 10;
        wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * 
sizeof(WordInfo));
        for (int i = 0; i < wtable->maxWords; i++) {
                llist_init(&wtable->wordArray[i].positions);
        }
}

// Add word to the tableand position. Position is added to the 
//corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
        // Find first word if it exists
        for (int i = 0; i < wtable->nWords; i++) {
                if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
                        // Found word. Add position in the list of positions
                        llist_insert_last(&wtable->wordArray[i].positions,position);
                        return;
                }
        }

        // Word not found.
        if (wtable->nWords >= wtable->maxWords) {
                wtable->maxWords = 2*(wtable->maxWords);
                wtable->wordArray = (WordInfo *) realloc 
(wtable->wordArray, (wtable->maxWords) * sizeof(WordInfo));
        }
        // Make sure that the array has space.
        // Expand the wordArray here.

        // Add new word and position
        wtable->wordArray[wtable->nWords].word = strdup(word);
        llist_insert_last(&wtable->wordArray[wtable->nWords].positions, 
position);
        wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
        fprintf(fd, "------- WORD TABLE -------\n");

        // Print words
        for (int i = 0; i < wtable->nWords; i++) {
                fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
                llist_print( &wtable->wordArray[i].positions);
        }
    }

// Get positions where the word occurs
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{       int a;

        for (a = 0; a < (wtable->nWords); a++)
        {
                if (strcmp(wtable->wordArray[a].word, word) == 0)
                {
                        return (&wtable->wordArray[a].positions);
                }
        }
        return NULL;
}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos;

// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
        char x;
        int a;
        a = 0;
        while ((x = getc(fd))!= EOF)  {
                if (isaletter(x))
                {
                        word[a] = x;
                        a = a + 1;
                        charCount++;

                }
                else if (!(isaletter(x)))
                {
                        word[a]= '\0';
                        charCount++;
                        if (strlen(word)> 0)
                        {
                                wordLength = strlen(word);
                                a=0;
                                return word;
                        }
 a=0;
                }
        }
        return NULL;


}

// Conver string to lower case
void toLower(char *s) {
        char c;
        int a;
        int length= strlen(s);

        for (a = 0; a < length; a++)
        {
                c = s[a];

                if (c >='A' && c <='Z')
                {
                        c += ' ';
                        s[a]=c;
                }
        }
}


// Read a file and obtain words and positions of the words and save them 
//in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int 
verbose)
{
        int end;
        FILE * fd;
        fd = fopen(fileName, "r");

        if (fd==NULL)
        {
                return 0;

        }

        char * ch = nextword(fd);

        while (ch!=NULL)
        {
                toLower(ch);
                end = charCount - strlen(ch) - 1;

                wtable_add(wtable,ch,end);
                if(verbose==1)
                printf("%d: word=%s, pos=%d\n", wordCount, ch, end);
                wordCount = wordCount + 1;
                ch = nextword(fd);

        }
fclose(fd);
        return 0;

}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
        WordInfo x;

        int a;
        int b;

        for (a = 0; a < (wordCount-1); a++)
        {
                for (b =(a+1); b < 526; b++)
                {
                        if(strcmp(wtable->wordArray[a].word, 
wtable->wordArray[b].word)>0)
                        {
                                x = wtable->wordArray[a];
                                wtable->wordArray[a] = 
wtable->wordArray[b];
                                wtable->wordArray[b] = x;
                        }
                }
        }

}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
        FILE * fd;
        fd = fopen(fileName, "r");

        if (fd== NULL)
        {
                return 0;

        }
        LinkedList * c;
        c = wtable_getPositions(wtable, word);

        printf("===== Segments for word \"%s\" in book \"%s\" =====\n", 
word, fileName);

        ListNode * a;
        a = c->head;
        while (a != NULL) {
                printf("---------- pos=%d-----\n", a->value);
                fseek(fd,a->value,SEEK_SET);
                printf("......");
                for (int b = 0; b < 200; b=b+1)
                printf("%c", fgetc(fd));
                printf("......\n");
                 a = a->next;

        }
        return 0;
}


