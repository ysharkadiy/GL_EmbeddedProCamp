/*
 * q.c
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

/**
 * struct Queue - It's structure with int array of MAX_QUEUE_ELEMENTS size.
 * @items: int array of data.
 * @Qfront: start index of the Queue.
 * @Qend: end index in the Queue.
 *
 */
static struct Queue
{
	int items[MAX_QUEUE_ELEMENTS]; // Initialization of Queue
	int Qfront; // start index of the Queue
	int Qend; // end index in the Queue
} q;

void initQueue()
{
	q.Qfront = -1;
	q.Qend = -1;
}

int isFull()
{
	if( (q.Qfront == q.Qend + 1) || (q.Qfront == 0 && q.Qend == MAX_QUEUE_ELEMENTS-1))
		return 1;
	else
		return 0;
}

int isEmpty()
{
	if(q.Qfront == -1)
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
			q.Qfront = 0;
		}
		q.Qend = (q.Qend + 1) % MAX_QUEUE_ELEMENTS;
		q.items[q.Qend] = value;
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
		element = q.items[q.Qfront];
		if (q.Qfront == q.Qend)
		{
			q.Qfront = -1;
			q.Qend = -1;
		} /* Q has only one element, so it's reset the queue after dequeing it.*/
		else
		{
			q.Qfront = (q.Qfront + 1) % MAX_QUEUE_ELEMENTS;
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
		printf(" Front -> %d \n", q.Qfront);
		printf(" Items -> ");
		for(i = q.Qfront; i!=q.Qend; i=(i+1)%MAX_QUEUE_ELEMENTS)
		{
			printf("%d ",q.items[i]);
		}
		printf("%d ",q.items[i]);
		printf("\n Tail -> %d \n",q.Qend);
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
		return q.items[q.Qfront];
	}
}
