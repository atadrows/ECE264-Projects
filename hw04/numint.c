// do not change this part, if you do, your code may not compile
//
/* test for structure defined by student */
#ifndef NTEST_STRUCT 
#include "numint.h"
#else 
#include "numint_key.h"
#endif /* NTEST_STRUCT */
//
// do not change above this line, if you do, your code may not compile
// This is the only file you have to include 

double simpson_numerical_integration(Integrand intg_arg) {
	double integral = 0.0;
	double width = (intg_arg.upper_limit - intg_arg.lower_limit) / intg_arg.n_intervals;

	double (*f) () = intg_arg.func_to_be_integrated;
	
	for(int i = 0; i < intg_arg.n_intervals; i++){
		double a = intg_arg.lower_limit + i * width;
		double b = intg_arg.lower_limit + (i + 1) * width;
		

		integral += (f(a) + 4 * f((a + b) / 2) + f(b)) *  (b - a) / 6;
	}

	return integral;
}
