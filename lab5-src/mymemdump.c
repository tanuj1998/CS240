
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.
    // p[0] will return the element 0 
    // p[1] will return the element 1 and so on
    
    // Print address of the beginning of p. You need to print it every 16 bytes
       // Print first byte as character. Only print characters >= 32 that are the printable characters.
	
        int a;
	int b = 0;
	int d = 0;
	int value = 0;


	fprintf(fd,"0x%016lX: ", (unsigned long) p);

	for(a = 0; a < len;){
	value = a;
	for(b = 0; (b < 16) && (a < len); b++){
	int c;
	c = p[a]&0xFF;

	fprintf(fd,"%02X ", c);

	a++;
	}

	a = value;
	fprintf(fd, " ");

	if(b != 16){
	for(d = 0; d < (16 - b); d++){
	
	fprintf(fd, "   ");
	
	      }
	}
	for(b = 0; (b < 16) && (a < len); (b++, a++)){
	int c;
	c = p[a]&0xFF;
        fprintf(fd, "%c", ((c >= 32) && (c <= 127))?c:'.');
	}

	if(a < len){
	fprintf(fd, "\n");
	fprintf(fd, "0x%016lX: ", (unsigned long) (&p[a]));
	}

	else{
	fprintf(fd, "\n");
		}
	}
}

