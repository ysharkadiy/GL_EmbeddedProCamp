/*
 * queue.c
 *
 *  Created on: Nov 24, 2019
 *      Author: YS
 *
 *      Ex.3. Create queue library based on array:
 *      -int Put(int);          // add element
 *      -int Get(*int);         // read element and remove from queue
 *      -Int Read(*int);        // read element without removing it from queue
 *
 */
#include <stdio.h>
#include "queue.h"
#define MAX_QUEUE_ELEMENTS 5

int items[MAX_QUEUE_ELEMENTS] = {};// Initialization of queue
int Qfront = -1;// start index of the queue
int Qend = -1;// end index in the queue

int isFull()
{
	if( (Qfront == Qend + 1) || (Qfront == 0 && Qend == MAX_QUEUE_ELEMENTS-1))
		return 1;
	else
		return 0;
}

int isEmpty()
{
	if(Qfront == -1)
		return 1;
	else
		return 0;
}

void putQueue(int value)
{
	if(isFull())
	{
		printf(" Queue is Full! \n");
	}
	else
	{
		if(isEmpty())
		{
			Qfront = 0;
		}
		Qend = (Qend + 1) % MAX_QUEUE_ELEMENTS;
		items[Qend] = value;
		printf(" Inserted -> %d \n", value);
	}
}

int getQueue()
{
	int element;
	if(isEmpty())
	{
		printf(" Queue is Empty! \n");
		return (-1);
	}
	else
	{
		element = items[Qfront];
		if (Qfront == Qend)
		{
			Qfront = -1;
			Qend = -1;
		} /* Q has only one element, so it's reset the queue after dequeing it.*/
		else
		{
			Qfront = (Qfront + 1) % MAX_QUEUE_ELEMENTS;
		}
		printf(" Deleted element -> %d \n", element);
		return(element);
	}
}

void displayQueue()
{
	int i;
	if(isEmpty())
		printf(" Empty Queue! \n");
	else
	{
		printf(" Front -> %d \n", Qfront);
		printf(" Items -> ");
		for(i = Qfront; i!=Qend; i=(i+1)%MAX_QUEUE_ELEMENTS)
		{
			printf("%d ",items[i]);
		}
		printf("%d ",items[i]);
		printf("\n Rear -> %d \n",Qend);
	}
}


int readQueue()
{
	if(isEmpty())
	{
		printf(" Queue is Empty! \n");
		return (-1);
	}
	else
	{
		return items[Qfront];
	}
}
