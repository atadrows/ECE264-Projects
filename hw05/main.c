#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "aux.h"
#include "util.h"
#include "fourier.h"

double _func(double);

int main(int argc, char ** argv) {

	if(argc != 6) {
		return EXIT_FAILURE;
	}

   	Integrand integrand;
	
	switch(atoi(argv[1])){
		case 1: integrand.func_to_be_integrated = &unknown_function_1;
				break;
		case 2: integrand.func_to_be_integrated = &unknown_function_2;
				break;
		case 3: integrand.func_to_be_integrated = &unknown_function_3;
				break;
		default: return EXIT_FAILURE;
	}

	integrand.lower_limit = atof(argv[2]);
	integrand.upper_limit = atof(argv[3]);
	integrand.n_intervals = atof(argv[4]);

	int n_terms = atoi(argv[5]);         // TODO: change to the real value

	Fourier fourier = {
		.intg      = integrand,
		.n_terms   = n_terms,
		.a_i       = malloc(sizeof(*fourier.a_i) * n_terms),
		.b_i       = malloc(sizeof(*fourier.b_i) * n_terms)
	};

	// If allocation of fourier.a_i and/or fourier.b_i failed, then free the
	// one that didn't fail and then exit with EXIT_FAILURE.
	if (fourier.a_i == NULL || fourier.b_i == NULL) {
		free(fourier.a_i);  // free(..) has not effect if its argument is NULL
		free(fourier.b_i);
		return EXIT_FAILURE;
	}

	fourier_coefficients(fourier);

	print_fourier_coefficients(fourier.a_i, fourier.b_i, 
                              fourier.n_terms);

	//function_plot(&unknown_function_2, integrand.lower_limit, integrand.upper_limit, fourier.a_i, fourier.b_i, fourier.n_terms, "cos.m");

	free(fourier.a_i);
	free(fourier.b_i);

	return EXIT_SUCCESS;
}

