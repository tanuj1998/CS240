
#include <stdio.h>

#include "array.h"

// Return sum of the array
double sumArray(int n, double * array) {
  double sum = 0;
  
  double * p = array;
  double * pend = p+n;

  while (p < pend) {
    sum += *p;
    p++;
  }

  return sum;
}

// Return maximum element of array
double maxArray(int n, double * array) {
  double maximum;

  maximum = 0;

  double * a = array;

  double * b = a + n;

  while(b > a){
        
	if(*a > maximum){

	maximum = *a;
	}

	a++;

    }
  return maximum;
}

// Return minimum element of array
double minArray(int n, double * array) {

  double minimum;
  minimum = 0;

  double * a = array;
  double * b = a + n;
  
  while(a < b){
    if(*a < minimum){

      minimum = *a;
      }

      a++;
      }
      return minimum;
}

// Find the position int he array of the first element x 
// such that min<=x<=max or -1 if no element was found
int findArray(int n, double * array, double min, double max) {
  double * a = array;
  double * b = a+n;
  double position;
  position = 0;

  while(b > a)
  {
  if((*a >= min) && (*a <= max)){
  return position;
  }

  position++;
  a++;
  }
  return -1;
}

// Sort array without using [] operator. Use pointers 
// Hint: Use a pointer to the current and another to the next element
int sortArray(int n, double * array) {

    double * a = array;
    double * b = a+n;
    double temporary;
    
    for(a; a < b; a++){
    
    double * c = (a + 1);
    for(c; c < b; c++){
     if(*a > *c){
     temporary = *a;
     *a = *c;
     *c = temporary;
     }
     }
     }
     return 1;
}

// Print array
void printArray(int n, double * array) {

     double * a = array;
     double * b = a+n;

     int c;
     c = 0;
     while(b > a){

     printf("%d:%f\n",c,*a);

     c++;
     a++;
     }
}

