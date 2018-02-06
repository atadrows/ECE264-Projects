#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include "hw02.h"

int main(int argc, char** argv) {
	
	fputc('\n', stdout);
	print_integer(0, 10, "");

	fputc('\n', stdout);
	print_integer(1, 10, "");

	fputc('\n', stdout);
	print_integer(9, 10, "");
	
	fputc('\n', stdout);
	print_integer(10, 10, "");

	fputc('\n', stdout);
	print_integer(11, 10, "");

	fputc('\n', stdout);
	print_integer(1000, 10, "");

	fputc('\n', stdout);
	print_integer(-1, 10, "");

	fputc('\n', stdout);
	print_integer(-9, 10, "");

	fputc('\n', stdout);
	print_integer(-10, 10, "");

	fputc('\n', stdout);
	print_integer(-11, 10, "");
	
	fputc('\n', stdout);
	print_integer(-1000, 10, "");

	fputc('\n', stdout);
	print_integer(2147483647, 10, "");

	fputc('\n', stdout);
	print_integer(-2147483648, 10, "");

	fputc('\n', stdout);
	print_integer(0, 2, "0b");

	fputc('\n', stdout);
	print_integer(1, 2, "0b");

	fputc('\n', stdout);
	print_integer(2, 2, "0b");

	fputc('\n', stdout);
	print_integer(3, 2, "0b");

	fputc('\n', stdout);
	print_integer(8, 2, "0b");

	fputc('\n', stdout);
	print_integer(-1, 2, "0b");

	fputc('\n', stdout);
	print_integer(-2, 2, "0b");

	fputc('\n', stdout);
	print_integer(-3, 2, "0b");

	fputc('\n', stdout);
	print_integer(-8, 2, "0b");

	fputc('\n', stdout);
	print_integer(0, 16, "0x");

	fputc('\n', stdout);
	print_integer(1, 16, "0x");

	fputc('\n', stdout);
	print_integer(15, 16, "0x");

	fputc('\n', stdout);
	print_integer(16, 16, "0x");

	fputc('\n', stdout);
	print_integer(17, 16, "0x");

	fputc('\n', stdout);
	print_integer(4096, 16, "0x");

	fputc('\n', stdout);
	print_integer(-1, 16, "0x");

	fputc('\n', stdout);
	print_integer(-15, 16, "0x");

	fputc('\n', stdout);
	print_integer(-16, 16, "0x");

	fputc('\n', stdout);
	print_integer(-17, 16, "0x");

	fputc('\n', stdout);
	print_integer(-4096, 16, "0x");

	fputc('\n', stdout);
	print_integer(0, 10, "$");

	fputc('\n', stdout);
	print_integer(1, 10, "$");

	fputc('\n', stdout);
	print_integer(9, 10, "$");

	fputc('\n', stdout);
	print_integer(10, 10, "$");

	fputc('\n', stdout);
	print_integer(11, 10, "$");

	fputc('\n', stdout);
	print_integer(1000, 10, "$");

	fputc('\n', stdout);
	print_integer(-1, 10, "$");

	fputc('\n', stdout);
	print_integer(-9, 10, "$");

	fputc('\n', stdout);
	print_integer(-10, 10, "$");

	fputc('\n', stdout);
	print_integer(-11, 10, "$");

	fputc('\n', stdout);
	print_integer(-1000, 10, "$");

	fputc('\n', stdout);
	print_integer(0, 36, "base36:");

	fputc('\n', stdout);
	print_integer(1, 36, "base36:");

	fputc('\n', stdout);
	print_integer(35, 36, "base36:");

	fputc('\n', stdout);
	print_integer(36, 36, "base36:");

	fputc('\n', stdout);
	print_integer(37, 36, "base36:");

	fputc('\n', stdout);
	print_integer(46656, 36, "base36:");

	fputc('\n', stdout);
	print_integer(-1, 36, "base36:");

	fputc('\n', stdout);
	print_integer(-35, 36, "base36:");

	fputc('\n', stdout);
	print_integer(-36, 36, "base36:");

	fputc('\n', stdout);
	print_integer(-37, 36, "base36:");

	fputc('\n', stdout);
	print_integer(-46656, 36, "base36:");

	return EXIT_SUCCESS;
}
