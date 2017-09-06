 #include <stdio.h>
#include <stdlib.h>

// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
        unsigned int n = bitmap;
        int i;
        for (i = 31; i >= 0; i--) {
        int temp = n & 1<<i;
        if(temp == 0) {
            printf("0");
        }
        else printf("1");
    }

    printf("\n");
    for (i = 31; i >= 0; i--) {
        printf("%d", i%10);
    }
    printf("\n");
}

// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {

  unsigned int mask = (1 << i);
  unsigned m= ~mask;
  unsigned int x;
  if(bitValue == 1){
     x = (*bitmap | mask);
     }
     else if(bitValue == 0){
     x = (*bitmap & m);
     }
     *bitmap = x;
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
      unsigned int size = sizeof(unsigned int);
      unsigned int maxPow = 1<<(size*8-1);
      int j;
      int a;
      for(j = 0; j < size*8; ++j){
       if(j == 31-i){
       a = bitmap & maxPow ? 1 : 0;
       break;
       }
       bitmap = bitmap<<1;
       }
       return a;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {

        unsigned int i;
	unsigned int count = 0;

	for(i = 0; i < 32; i++){
	if(bitmap % 2 != 0){
	count++;
	}
	bitmap = bitmap >> 1;
	}
	if(bitValue == 1){
	return count;
	}
	else {
	return 32-count;
	}
}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
   int i;
   int max = 0;
   int count = 0;
   int pos = 0;
   for(i = 0; i < 32; i++){
   int j = getBitAt(bitmap,i);
   if(j == 1){
   count++;
   }
   else{
   if(count > max){
   pos = i-count;
   max = count;
   }
   count = 0;
   }
   }
   *position = pos;
   return max;
}


