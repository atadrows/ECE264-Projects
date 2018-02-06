#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L

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

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, 
                                                 double (*cos_sin)(double)) {
	double integral = 0.0;
	double width = (intg_arg.upper_limit - intg_arg.lower_limit) / intg_arg.n_intervals;

	double (*f) () = intg_arg.func_to_be_integrated;
	
	for(int i = 0; i < intg_arg.n_intervals; i++){
		double a = intg_arg.lower_limit + i * width;
		double b = intg_arg.lower_limit + (i + 1) * width;
		double L = (intg_arg.upper_limit - intg_arg.lower_limit) / 2;

		double f_a = f(a) * cos_sin(n * M_PI * a / L);
		double f_aplusb = f((a + b) / 2) * cos_sin(n * M_PI * ((a + b) / 2) / L);
		double f_b = f(b) * cos_sin(n * M_PI * b / L);

		integral += (f_a + 4 * f_aplusb + f_b) *  (b - a) / 6;
	}

	return integral;

}

void fourier_coefficients(Fourier fourier_arg) {
	double l = (fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit) / 2;
	for (int i = 0; i < fourier_arg.n_terms; i++) {
		fourier_arg.a_i[i] = (1 / l) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, &cos);
		fourier_arg.b_i[i] = (1 / l) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, &sin);
	}
}

