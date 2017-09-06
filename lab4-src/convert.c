#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv) 
{
	if (argc != 4) {
		printf("Usage:  convert <basefrom> <baseto> <number>\n");
		exit(1);
	}

	int baseFrom = 0;
	int baseTo = 0;
	long signed int a;
	long signed int b;
	long signed int x = 0;
	char word[15];
	int i = 0;

	char numbers[25] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
	int converted[64];
	sscanf(argv[1], "%d", &baseFrom);
	sscanf(argv[2], "%d", &baseTo);
	sscanf(argv[3], "%s", word);
	sscanf(argv[3], "%ld", &a);
	sscanf(argv[3], "%ld", &x);

	printf("Number read in base %d: %s\n", baseFrom, word);
	if(baseFrom < 10) {
		int j;

		for(j = 0; j < strlen(word); j++) {
			int y = word[j] - 48;
			if (y >= baseFrom) {
				printf("Wrong digit in number.\n");
				exit(1);
			}

		}

	}
	b = strtol(word, NULL, baseFrom);
	printf("Converted to base 10: %ld\n", b);
	while (b != 0)
	{
		converted[i] = b % baseTo;
		b = b/baseTo;
		++i;
	}
	--i;
	printf("Converted to base %d: ", baseTo);
	for(; i >=0; i--) 
	{
		printf("%c", numbers[converted[i]]);
	}
	printf("\n");

}

