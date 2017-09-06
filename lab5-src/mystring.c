
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
        char * temp = s;
	int a = 0;
	while(*temp != '\0'){
	a++;
	temp++;
	}
	return a;
}

char * mystrcpy(char * dest, char * src) {
	char * a = src;
	char * b = dest;
	while(*a){
	*b = *a;
	*b++;
	*a++;
	}
	*b = '\0';
	return dest;
}

char * mystrcat(char * dest, char * src) {
	char * a = dest;
	while(*a != '\0'){
	    a++;
	    }
	    while(*src != '\0'){
	    *a = *src;
	    a++;
	    src++;
	    }
	    *a = '\0';
	    return dest;
}

int mystrcmp(char * s1, char * s2) {
	int a;
	int b;
	
	a = 0;
	b = 0;
	while(*s1 != '\0'){
	a++;
	s1++;
	}
	while(*s2 != '\0'){
	b++;
	s2++;
	}
	if(b > a){
	return -1;
	}
	else if(b < a){
	return 1;
	}
	else{
	return 0;
	}
	return -1;
}

char * mystrstr(char * hay, char * needle) {
	char * p = hay;
	while(*p != '\0'){
	char * answer = p;
	char * m = needle;
	while(*p != '\0' && *m != '\0' && *p == *m){
	p++;
	m++;
	}
	if(*m == '\0')
	return answer;
	p++;
	}
	return NULL;
}

char * mystrdup(char * s) {
         char * a = s;
	 int x = 0;
	 while(*a != '\0'){
	 x++;
	 a++;
	 }
	 char * duplicate = (char*)malloc(sizeof(char*));
	 char * b = duplicate;
	 while(*s != '\0'){
	    *b = *s;
	    s++;
	    b++;
	   }
	   *b = '\0';
         return duplicate;
}

char * mymemcpy(char * dest, char * src, int n)
{
        char * a = src;
	char * b = dest;
	int x;
	for(x = 0; x < n; x++){
	*b = *a;
	*b++;
	*a++;
	}

	return dest; 
}

