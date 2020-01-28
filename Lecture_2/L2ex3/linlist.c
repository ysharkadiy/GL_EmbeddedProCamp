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

	while(head->next != NULL)
	{
		head = head->next;
	}
	head->next = new;
}

void ListRemoveFromEnd(LinList *head)
{
	if (head == NULL)
	{
		printf(" Linked List is empty!\n");
	}
	else
	{
		if (head->next == NULL)
		{
//			free(head);
//			head = NULL;
			head->data = '\0';
			printf(" The last element from Linked List was removed!\n");
		}
		else
		{
			while (head->next->next != NULL)
			{
				head = head->next;
			}
			free(head->next);
			head->next = NULL;
		}
	}
}

void ListIs(LinList *head, char data)
{
	unsigned int index = 0;
	bool flagToFindData = false;
	while(head->next != NULL)
	{
		if(head->data != data)
		{
			head = head->next;
			index++;
		}
		else
		{
			flagToFindData = true;
			printf(" Num of element : %c\n Index[0:end] of element : %u", data, index);
			head = head->next;
			index++;
		}
	}
	if(flagToFindData == 0)
	{
		printf(" Message: The data %c didn't find in that LinkedList!\n", data);
	}
}

void DisplayingLinkedList(LinList *head)
{
	if ( (head == NULL) || (head->data == '\0') )
	{
		printf(" Linked List is empty!\n");
	}
	else
	{
		printf("\n List elements are - ");
		while (head != NULL)
		{
			printf("%c---> ", head->data);
			head = head->next;
		}
		printf("\n");
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

