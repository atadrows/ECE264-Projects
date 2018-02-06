#include <stdio.h>
#include <stdlib.h>
#include "mintf.h"

int main(int argc, char ** argv){

	mintf("x = %d\n", 25);
	mintf("I have %d hampsters and %d fish\n", 6, 1);
	mintf("%d is %x in hex\n", 12, 12);
	mintf("%d is %b in binary\n", -12, -12);
	mintf("Bank balance: %$\n", 13.1);
	mintf("%$ is like a milli where I'm from\n", 15.654);
	mintf("Am poor. Have %$ monies\n", -2.169);
	mintf("Unnecessary argument: %s", "\"here I am\"\n");
	mintf("My favorite char = %c\n", 'b');
	mintf("My second fav char = %c\n", 51);
	mintf("%d%% of statistics are made up\n", 35);
	mintf("there is an error of 3%% percent\n");
	mintf("Lone parent: %\n", 12984);

	return EXIT_SUCCESS;
}
