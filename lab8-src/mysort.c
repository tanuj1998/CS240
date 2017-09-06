#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//

//
// See test_sort to see how to use mysort.
/**
 * @brief Arbitrary sort func
 *
 * Sort an array of element of any type
 * using "compFunc" to sort the elements.
 * 
 * The elements are sorted such as:
 * 
 * if ascending != 0
 *   compFunc( array[ i ], array[ i+1 ] ) <= 0
 * else
 *   compFunc( array[ i ], array[ i+1 ] ) >= 0
 * 
 * @param n Number of elements.
 * @param elementSize Size of each element.
 * @param array Pointer to an array of arbitrary type.
 * @param ascending Boolean controlling the direction of the sort.
 * @param compFunc Comparison funciton.
 **/
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> 
	     CompareFunction compFunc )  // Comparison function.
{
	// Add your code here
	void * temporary;
	temporary = (void *)malloc(elementSize);
	int a; 
	int b;
	void * function1;
	void * function2;

	for(a = 0 ; a < n ; a = a+1) {

		for(b = 0 ; b < (n - 1) ;b = b+1) {

			function1 = (void*)( (char *)array + (b) * elementSize);
			function2 = (void*)( (char *)array + (b + 1) * elementSize);

			if ((ascending == 0) && ((*compFunc)(function1 ,function2) <= 0))
			{	
				memcpy(temporary, function1, elementSize);
				memcpy(function1, function2, elementSize);
				memcpy(function2, temporary, elementSize);
			
			}

			if ((ascending == 1) && ((*compFunc)(function1 ,function2) >= 0))
                        {
				memcpy(temporary, function1, elementSize);
				memcpy(function1, function2, elementSize);
				memcpy(function2, temporary, elementSize);
			
			}
			
		}
	}

	free(temporary);
}
