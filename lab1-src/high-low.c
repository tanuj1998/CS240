#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {

    printf("Welcome to the High Low game...\n");
	char option;
	char ans;
	int low = 1;
	int high = 100;
        game_start:
	printf("Think of a number between 1 and 100 and press <enter>");
    getchar();
       low = 1;
       high = 100;
    for(;;){
    int mid = (low+high)/2;
	printf("Is it higher than %d? (y/n)\n", mid);
    ans = getchar();
    getchar();
    if(ans == 'y')
     {
    	low = mid+1;
        
     }
    else if(ans == 'n')
      {
    	high = mid-1; 
        
      }
     else {
          printf("Type y or n\n");
       }
        if(high < low)
        {
        printf("\n>>>>>> The number is %d\n\n",low);
        break;
        }
     }
        printf("Do you want to continue playing (y/n)?");    	
        scanf("%c", &option);
        getchar();
    	if(option == 'y')
    	{
   		goto game_start;
            
    	}
    	else if(option == 'n')
    	{
    		
    	}
    	else 
    	{
    		printf("Type y or n\n");
    	}
	return 0;

}

