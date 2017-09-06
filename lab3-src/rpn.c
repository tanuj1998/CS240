#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"
FILE * fd;
double pop();
double rpn_eval(char * fileName, double x) {
  char *word;
  double a,b,c;
  fd = fopen(fileName, "r");
  while( ( word = nextword(fd)) != NULL){
  if( word[0] != '+' && word[0] != '-' && word[0] != '*' && word[0] != '/' && word[0] != 'p' && word[0] != 's' && word[0] != 'c' && word[0] != 'l' && word[0] !='e' && word[0] != 'x') {
  stack_push(atof(word));
  }
  else{
  if(word[0] == 'x')
  {
  stack_push(x);
  }
  else if(word[0] == '+')
  { if(stack_is_empty())
  {
  printf("Stack Underflow\n");
  fclose(fd);
  exit(1);
  }
  a = pop();
  b = pop();
  c = a + b;
  stack_push(c);
  }
  else if(word[0] == '-')
  { if(strlen(word) > 1)
  {
  stack_push(atof(word));
  continue;
  }
  if(stack_is_empty())
  {
     printf("Stack Underflow\n");
  }
  else {
  a = pop();
  b = pop();
  c = b - a;
  stack_push(c);
  }
  }
  else if(word[0] == '*')
  {
   if(stack_is_empty())
   {
   printf("Stack Underflow\n");
   }
   a = pop();
   b = pop();
   c = a * b;
   stack_push(c);
   
  }
  else if(word[0] == '/')
  {
   if(stack_is_empty())
   {
   printf("Stack Underflow");
   }
   a = pop();
   b = pop();
   c = b / a;
   stack_push(c);
  }
  else if(word[0] == 'p')
  {
  if(stack_is_empty())
  {
  printf("Stack Underflow\n");
  }
  stack_push( pow(stack_pop(),stack_pop()));
  }
  else if(word[0] == 's')
  {
   if(stack_is_empty())
   {
   printf("Stack Underflow\n");
   }
  stack_push(sin(stack_pop()));
  }
  else if(word[0] == 'c')
  {
  if(stack_is_empty())
  {
  printf("Stack Underflow\n");
  }
  stack_push(cos(stack_pop()));
  }
  else if(word[0] == 'l')
  { 
  stack_push(log(stack_pop()));
  }
  else if(word[0] == 'e')
  {
  if(stack_is_empty())
  {
  printf("Stack Underflow\n");
  }
  stack_push(exp(stack_pop()));
  }
  }
  }
  double result = stack_pop();
  return result;
}
 double pop()
 {
   if(stack_is_empty())
  {
  printf("Stack underflow\n");
  fclose(fd);
  exit(1);
  }
  else 
  {
  return stack_pop();
  }
 }

