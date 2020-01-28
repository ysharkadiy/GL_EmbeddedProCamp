/*
 * main.c
 *
 *  Created on: Nov 24, 2019
 *      Author: YS
 *
 *      Ex.2. Create stack library based on linked list:
 *      -int Push(int);    // add element
 *      -int Pop(*int);    // read element and remove from stack
 *      -int Read(*int);   // read element without removing it from stack
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <stdbool.h>


int main()
{
	/**
	 * DOC: Theory of Operation
	 * The Eclipse console has buffering problems on Windows.
	 * Basically, it doesn't flush the streams when a newline is received.
	 * (Unlike a normal windows console window).
	 * So, I had added the following lines in the start of the main function:
	 */
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf(" Ex.2. Stack library based on linked list. \n");


	// initialization of variable
	stack_t *top_of_steck = NULL;
	int read_from_stack, pop_from_stack;

	printf(" IsEmpty = %d\n", IsEmpty(top_of_steck));
	printf(" IsFull = %d\n", IsFull(top_of_steck));
	for(int i = 0; i<5; i++)
	{
		Push(&top_of_steck, rand()%10);
		DisplayingStack(top_of_steck);
	}
	printf(" IsEmpty = %d\n", IsEmpty(top_of_steck));
	printf(" IsFull = %d\n", IsFull(top_of_steck));

	pop_from_stack = Pop(&top_of_steck);
	printf(" Variable pop_from_stack = %d \n", pop_from_stack);

    DisplayingStack(top_of_steck);
    read_from_stack = Read(top_of_steck);
	printf(" Variable read_from_stack = %d \n", read_from_stack);
	DisplayingStack(top_of_steck);

	//Dynamic free the previously allocated memory.
    DynamicMemoryFREE(top_of_steck);

    printf("\n Have a good day :) \n Work was finished.");
    return 0;
}
