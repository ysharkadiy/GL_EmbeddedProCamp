/*
 * main.c
 *
 *  Created on: Nov 15, 2019
 *      Author: YS
 *
 *      Ex6: Write a C program to print all numbers between 1 to 500
 *      which divided by a number specified by user.
 *
 */
#include <stdio.h>

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
	int divider, max_number = 500, min_number = 1;
	printf(" Ex.6. Print all number which divided by a number specified by user from 1 to 500. \n");
	// read divider from customer
	printf(" Enter divider: ");
	scanf("%d", &divider);
	for(int i = min_number; i <= max_number; i++)
	{
		if (i%divider == 0)
		{
			printf("%d\n", i);
		}
	}
	printf(" Have a good day :) \n Work was finished.");
	return 0;
}
