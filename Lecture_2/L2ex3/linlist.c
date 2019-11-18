/*
 * linlist.c
 *
 *  Created on: Nov 18, 2019
 *      Author: YS
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linlist.h"

void ListAddToEnd(LinList *head, char newValue)
{
	LinList *new;
	new = malloc(sizeof(LinList));
	new->data = newValue;
	new->next = NULL;

	LinList *temp = head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
}

void ListRemoveFromEnd(LinList *head)
{
	LinList *temp = head;
	while(temp->next->next != NULL)
	{
		temp = temp->next;
	}
	free(temp->next);
	temp->next = NULL;
}

void ListIs(LinList *head, char data)
{
	LinList *temp = head;
	unsigned int index = 0;
	bool flagToFindData = false;
	while(temp->next != NULL)
	{
		if(temp->data != data)
		{
			temp = temp->next;
			index++;
		}
		else
		{
			flagToFindData = true;
			printf("\n Num of element : %c\n Index of element : %u", data, index);
			temp = temp->next;
			index++;
		}
	}
	if(flagToFindData == 0)
	{
		printf("\n Message: The data %c didn't find in that LinkedList!", data);
	}
}

void DisplayingLinkedList(LinList *head)
{
	LinList *temp = head;
	printf("\n List elements are - ");
	while(temp != NULL)
	{
		printf("%c---> ", temp->data);
		temp = temp->next;
	}
}

void DynamicMemoryFREE(LinList *head)
{
	LinList *temp = head;
	do{
		while(temp->next->next != NULL)
		{
			temp = temp->next;
		}
		free(temp->next);
		temp->next = NULL;
		temp = head;
	}
	while(temp->next == NULL);
	free(temp);
}

