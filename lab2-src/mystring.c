
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
        int a = 0; 

        while(s[a] != '\0')
        {
          a++;
        }
      	return a;
}

char * mystrcpy(char * dest, char * src) {
        int a;

        for(a = 0; src[a] != '\0'; ++a){
        dest[a] = src[a];
        }
        dest[a] = '\0';
	return dest;
}

char * mystrcat(char * dest, char * src) {
       
          int a,b;
          for(a = 0; dest[a] != '\0'; a++);
          for(b = 0; src[b] != '\0'; b++)
          {
              dest[a+b] = src[b];
          }

          dest[a+b] = '\0';
          return dest;         
}

int mystrcmp(char * s1, char * s2) {
            for(; *s1 == *s2; ++s1, ++s2)
            
            if( *s1 == 0){
              return 0;
            }
            
            return *(char *)s1 < *(char *)s2 ? -1 : 1;
             
}

char * mystrstr(char * hay, char * needle) {
        int a;
        int b;
         				
        b = strlen(needle);
        if(!b){
        return (char *) hay;
        }
        a = strlen(hay);
        while(a >= b)
         {
           a--;
          if(!memcmp(hay,needle,b)){
          return (char *)hay;
          }
          hay++;
        }
	return NULL;
}

char * mystrdup(char * s) {
        char *b2 = malloc(strlen(s));

        if(b2 != NULL)
        {
          strcpy(b2,s);
        }
	return (b2);
}

char * mymemcpy(char * dest, char * src, int n)
{
        char *a = (char *) dest, *b = (char *) src;

        while(n--)
        {
          *a++ = *b++;
        }
	return dest;
}

