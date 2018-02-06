#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"

void _printPrefix(char*);
void _printInBase(unsigned int, int);
void _printStringBackwards(char[], int);
int _pow(int, int);
int _numInBase(unsigned int, int);
void mintf(const char*, ...);
void _print_double(double, int, char*);
void _print_string(char*);

void mintf(const char* format, ...){

	va_list ap;
	va_start(ap, format);

	for(int i = 0; format[i] != '\0'; i++){
		if(format[i] == '%'){
			switch(format[i+1]){
				case 'd': print_integer(va_arg(ap, int), 10, "");
						  break;
				case 'x': print_integer(va_arg(ap, int), 16, "0x");
						  break;
				case 'b': print_integer(va_arg(ap, int), 2, "0b");
						  break;
				case '$': _print_double(va_arg(ap, double), 2, "$");
						  break;
				case 's': _print_string(va_arg(ap, char*));
						  break;
				case 'c': fputc(va_arg(ap, int), stdout);
						  break;
				case '%': fputc('%', stdout);
						  break;
				default: fputc('%', stdout);
						 continue;
			}
			i++;
		} else {
			fputc(format[i], stdout);
		}
	}

	va_end(ap);
}


void _print_string(char* s){
	for(int i = 0; s[i] != '\0'; i++){
		fputc(s[i], stdout);
	}
}

// Prints a double to (num_places) places after the decimal with the prefix (prefix)
void _print_double(double n, int num_places, char* prefix){
	print_integer((int) n, 10, prefix);

	n -= (int) n;

	if(n < 0) {
		n = -n;
	}

	fputc('.', stdout);

	for(int i = 0; i < num_places; i++){
		n *= 10;
		print_integer((int) (n + 0.00001), 10, "");
		n -= (int) (n + 0.00001);
	}
}

void print_integer(int n, int radix, char* prefix) {
	
	unsigned int pos_n;

	if(radix > 36 || radix < 2){
		return;
	}

	if(n < 0) {
		fputc('-', stdout);
		pos_n = -n;
	} else {
		pos_n = n;	
	}

	_printPrefix(prefix);

	if (n == 0) {
		fputc('0', stdout);
		return;
	}

	_printInBase(pos_n, radix);
}

int _numInBase(unsigned int n, int base) {
	int i;
	for(i = 0; n > 0; i++){
		n /= base;
	}
	return i-1;
}

int _pow(int base, int exp) {
	int result;
	if(exp > 0) {
		result = base;
		for(int i = 1; i < exp; i++) {
			result *= base;
		}
	} else {
		result = 1; 
	}
	return result;
}

void _printInBase(unsigned int n, int base) {
	int greatestExp = _numInBase(n, base);

	for(int i = greatestExp; i >= 0; i--){
		int pow = _pow(base, i);
		int digit = n / pow;

		if(n < pow) {
			digit = 0;
		}
		n %= pow;

		if(digit <= 9){
			fputc('0' + digit, stdout);
		} else if(digit > 9){
			fputc('a' + digit - 10, stdout);
		}
	}
	
}

void _printPrefix(char* prefix) {

	for (int i = 0; prefix[i] != '\0'; i++) {
		fputc(prefix[i], stdout);
	}
}
