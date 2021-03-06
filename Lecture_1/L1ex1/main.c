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
	MSB = ((MSB & 0xFF) <<8 ) | (MSB >>8);
	return MSB;
}

uint32_t swap_32(uint32_t MSB)
{
	MSB = (swap_16(MSB)<<16) | (swap_16(MSB>>16));
	return MSB;
}

uint64_t swap_64(uint64_t MSB)
{
	MSB = ((uint64_t)(swap_32(MSB))<<32) | (swap_32(MSB>>32));
	return MSB;
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
	test_value = 0x1122334455667788;

	printf(" Ex.1. Swap MSB to LSB in uint16_t, uint32_t, uint64_t. \n");

	printf(" Result 16 = 0x%x\n", swap_16(0xABCD));
	printf(" Result 32 = %#x\n", swap_32(0x1A2B3C4D));
	//printf(" Result 64 = %#x\n", swap_64(test_value));
	// included for using macros and try to print uint64_t
	printf(" Result 64 = %#" PRIXMAX "\n", swap_64(test_value));


//	// second method for printing
//	uint64_t input;
//	input = swap_64(test_value);
//	uint8_t i;
//	unsigned char byte;
//	for (int i = 0; i < sizeof(input); i++) {
//		byte = ((unsigned char*) (&input))[i];
//		printf("%02X ", byte);
//	}
	printf(" Have a good day :) \n Work was finished.");
	return 0;
}
