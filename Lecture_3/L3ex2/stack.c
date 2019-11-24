/*
 * stack.c
 *
 * Create stack library based on linked list:
 *      -int Push(int);    // add element
 *      -int Pop(*int);    // read element and remove from stack
 *      -int Read(*int);   // read element without removing it from stack
 *
 *  Created on: Nov 24, 2019
 *      Author: YS
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define MAX_STACK_ELEMENTS 10

void Push(stack_t **topRef, int newValue)
{
	stack_t *top = *topRef;
	// check if stack (heap) is full. Then inserting an element would
	// lead to stack overflow
	if (IsFull(top))
	{
		printf(" Stack Overflow! \n");
		DynamicMemoryFREE(top);
		exit(1);
	}
	// create new node temp and allocate memory
	stack_t *new;
	new = (stack_t*)malloc(sizeof(stack_t));
	// initialize data into temp data field
	new->data = newValue;
	// put top pointer reference into temp link
	new->next = top;
	// make temp as top of Stack
	top = new;
	*topRef = top;
}

int IsEmpty(stack_t *top)
{
	if (top == NULL)
		return 1;
	else
		return 0;
}

int IsFull(stack_t *top)
{
	stack_t *temp = top;
	int el_num = -1;
	while(temp != NULL)
	{
		temp = temp->next;
		el_num++;
	}
	if (el_num>=MAX_STACK_ELEMENTS-1)
		return 1;
	else
		return 0;
}

int Read(stack_t *top)
{
	// check for empty stack
	if (IsEmpty(top))
		exit(1);
	else
		return top->data;
}

int Pop(stack_t **topRef)
{
	stack_t *top = *topRef;
	stack_t *temp = top;
	int pop_data = 0;
	// check for stack underflow
	if (IsEmpty(top))
	{
		printf(" Stack Underflow! \n");
		exit(1);
	}
	else
	{
		// assign second node to top
		top = top->next;
		// destroy connection between first and second
		temp->next = NULL;
		printf(" Pop: Was removed from stack %d---> \n", temp->data);
		pop_data = temp->data;
		*topRef = top;
		// release memory of top node
		free(temp);
	}
	return pop_data;
}

void DisplayingStack(stack_t *top)
{
	stack_t *temp = top;
	printf(" List elements are - ");
	while(temp != NULL)
	{
		printf("%d---> ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

void DynamicMemoryFREE(stack_t *top)
{
	stack_t *temp = top;
	while(temp->next == NULL)
	{
		while(temp->next->next != NULL)
		{
			temp = temp->next;
		}
		free(temp->next);
		temp->next = NULL;
		temp = top;
	}
	free(temp);
}
