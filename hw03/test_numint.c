#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

//
// You do not have to include numint.h here because you are not 
// calling the function function_to_be_integrated here.
//
#include "numint.h"

//
// Fill in the correct statements to complete the main(..) function.
//
// We expect four arguments:
//
// The first argument is two characters from the sets {"-m", "-t"}
// -m: run mid_point_numerical_integration
// -t: run trapezoidal_numerical_integration
// otherwise: return EXIT_FAILURE
//
// To run any of the two functions, expect the next three arguments
// to be the lower limit of the integration (double), the upper limit
// of the integration (double), and the number of intervals for the
// integration (int).
//
// If the number of intervals is less than 1, set it to 1.
//
// Use atof to convert an argument to a double.
//
// Use atoi to convert an argument to an int.
//
// After you have numerically integrated the function, print the 
// return value, and return EXIT_SUCCESS

int whichflag(char[]);

int main(int argc, char * * argv) {
	double integral = 0.0;
	/*
	integral = trapezoidal_numerical_integration(0, 2, 10);
	printf("%.10e\n", integral);

	integral = mid_point_numerical_integration(2, 0, 10);
	printf("%.10e\n", integral);
	*/
	if(argc == 5) {
		double lower_limit = atof(argv[2]);
		double upper_limit = atof(argv[3]);
		int n_intervals = atoi(argv[4]);

		if(n_intervals < 1) {
			n_intervals = 1;
		}

		switch(whichflag(argv[1])){
			case 1: integral = mid_point_numerical_integration(lower_limit, upper_limit, n_intervals);
					break;
			case 0: integral = trapezoidal_numerical_integration(lower_limit, upper_limit, n_intervals);
					break;
			case -1: return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}

	printf("%.10e\n", integral);

	return EXIT_SUCCESS;
}

//-m: 1, -t: 0, neither: -1
int _which_flag(char str[]) {
	if(str[0] == '-' && str[1] == 'm' && str[2] == '\0'){
		return 1;
	} else if(str[0] == '-' && str[1] == 't' && str[2] == '\0'){
		return 0;
	} else {
		return -1;
	}
}

