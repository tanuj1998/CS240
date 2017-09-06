#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 void filedump(char * p , int len) {
          
	  int a;
	  char solution[17];

          long int location;
	  location= 0;
          long int change;
	  change = 0;

          for(a = 0; a<len; a++) 
	  {
 
                  if(len >= 1000000)  {
                          if(p[a] == '\0')
                            break;
                  }
                  if(a%16==0) {
                          printf("0x%016lX: ", (unsigned long)location + change );
                  
		  }
                  int c;
		  c = p[a]&0xFF;
                  printf("%02X ", c);
 
                  solution[a%16] = (((c >= 32) && (c < 127))? (char)c : '.');
 
                  if((a + 1)%16==0)  {
                          solution[a % 16 + 1] = '\0';
                          printf(" %s\n",solution);
                  }
 
                  change++;
 
 
          }
 
          if(a%16 !=0) {
                  solution[a%16] = '\0';
                  for(a = a % 16; (a < 16); a++) {
                          printf("   ");
                  }
                  printf(" %s\n",solution);
          }
 
 
  }
 

 int main(int argc, char **argv) {
          int mbytes;
	  mbytes = 0;
          if(2 > argc)
          {
                 printf("Usage: myfiledump filename [maxbytes]\n");
                  exit(1);
          }

          char* fileName = argv[1];
          FILE* fd = fopen(fileName,"r");
          
	  if(fd == NULL){
                  
		  printf("Error opening file \"%s\"\n",fileName);
                  exit(1);
          }
          
	  fseek(fd, 0L, SEEK_END);
	  int fileSize = ftell(fd);
	  fseek(fd, 0L, SEEK_SET);

          char * f;
	  f =(char * )malloc(fileSize);
          fread(f,(fileSize+1),1,fd);

          if(argc ==3){
                  
          mbytes=atoi(argv[2]);
	  if(mbytes < fileSize){
	  filedump(f, mbytes);
	  }
	  else{
	  filedump(f, fileSize);
	  }
	 } 
          
	 else{
          filedump(f , fileSize);
          }
          return 1;
  }
