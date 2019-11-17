/*
 * main.c
 *
 *  Created on: Nov 14, 2019
 *      Author: YS
 *
 *      Ex1: Write swap16,  swap32, swap64 functions
 *      that swap, bytes in uint16_t, unit32_t, and uint64_t functions.
 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h> // included for using macros and try to print uint64_t

// body of function without declaration
uint16_t swap_16(uint16_t MSB)
{
	uint16_t LSB;
	LSB = ((MSB & 0xFF) <<8 ) | (MSB >>8);
	return LSB;
}
uint32_t swap_32(uint32_t MSB)
{
	uint32_t LSB;
	LSB = (swap_16(MSB)<<16) | (swap_16(MSB>>16));
	return LSB;
}
uint64_t swap_64(uint64_t MSB)
{
	uint64_t LSB;
	LSB = (swap_32(MSB)<<32) | (swap_32(MSB>>32));
	return LSB;
}

int main(void)
{
	/*
	 * The Eclipse console has buffering problems on Windows.
	 * Basically, it doesn't flush the streams when a newline is received.
	 * (Unlike a normal windows console window).
	 * So, I had added the following lines in the start of the main function:
	 */
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// initialization of variable
	uint64_t test_value;

	printf(" Ex.1. Swap MSB to LSB in uint16_t, uint32_t, uint64_t. \n");

	printf(" Enter test_value for swap: ");
	scanf("%x", &test_value);
	printf("Bytes %d   Value %#x   Address %#x \n", sizeof(test_value), test_value, &test_value);
	printf(" Result 16 = 0x%x\n", swap_16(test_value));
	printf(" Result 32 = %#x\n", swap_32(test_value));
	// included for using macros and try to print uint64_t
	printf("%" PRIXMAX "\n", swap_64(test_value));
	printf(" Result 64 = %#x\n", swap_64(test_value));

	printf(" Have a good day :) \n Work was finished.");
	return 0;
}
