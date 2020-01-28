/*
 * main.c
 *
 *  Created on: Nov 24, 2019
 *      Author: YS
 *
 *      Ex.3. Create queue library based on array:
 *      -int Put(int);          // add element
 *      -int Get(*int);         // read element and remove from queue
 *      -Int Read(*int);        // read element without removing it from queue
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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
	printf(" Ex.3. Queue library based on array. \n");

	// initialization of variable
	int queue_element = 0;

   // before using Queue Abstract Data Type (ADT) should initQueue
	initQueue();

	//getQueue is not possible on empty queue
	getQueue();
	printf(" Enter value which will be contain to Queue : \n");
	for(int i=0; i<5; i++)
	{
		queue_element = rand()%50;
		printf(" el[%d] = %d", i, queue_element);
//		scanf("%d", &queue_element);
		//putQueue 5 elements
		putQueue(queue_element);
	}
	displayQueue();
	//getQueue removes element entered first i.e. 1
	getQueue();
	//Now we have just 4 elements
	displayQueue();
	// try read the first out element without removing
	printf(" readQueue = %d \n", readQueue());

	printf("\n Have a good day :) \n Work was finished.");
	return 0;
}





