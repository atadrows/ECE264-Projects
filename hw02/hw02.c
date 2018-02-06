#include<stdio.h>

void _printPrefix(char*);
void _printInBase(unsigned int, int);
void _printStringBackwards(char[], int);
int _pow(int, int);
int _numInBase(unsigned int, int);

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
			//changedBaseNumber[i] = '0' + n % base;
		} else if(digit > 9){
			fputc('a' + digit - 10, stdout);
			//changedBaseNumber[i] = 'a' + remainder;
		}
	}
	
}

void _printPrefix(char* prefix) {

	for (int i = 0; prefix[i] != '\0'; i++) {
		fputc(prefix[i], stdout);
	}
}

