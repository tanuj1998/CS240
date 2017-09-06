
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
	int c;
	int lines=0;
        
	printf("Program that counts lines.\n");
	char * fileName = argv[1];
	FILE * fp = fopen(fileName, "r");
	if(fp == NULL){
	printf("Could not open file %s\n", fileName);
	exit(1);
	}
	while( (c = fgetc(fp)) != EOF){
	if(c == '\n')
	  lines++;
        }
	fclose(fp);
	printf("Total lines: %d\n", lines);
	exit(0);
}
