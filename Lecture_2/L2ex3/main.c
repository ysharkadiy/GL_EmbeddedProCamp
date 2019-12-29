/*
 * main.c
 *
 *  Created on: Nov 18, 2019
 *      Author: YS
 *
 *      Ex.3.Create linked list library with functions (ListAdd(), ListIs(), ListRemove()).
 *      New elements in list should be dynamically allocated.
 */
#include <stdio.h>
#include <stdlib.h>
#include "linlist.h"
#include <stdbool.h>


int main()
{
	/*
	 * The Eclipse console has buffering problems on Windows.
	 * Basically, it doesn't flush the streams when a newline is received.
	 * (Unlike a normal windows console window).
	 * So, I had added the following lines in the start of the main function:
	 */
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// initialization of flag
	bool do_add_random_value = true;

	// initialization of variable
	LinList *first_list = NULL;
	first_list = malloc(sizeof(LinList));

    printf(" Ex.3. Create linked list library. \n");

    if (first_list == NULL)
    {
    	printf(" Malloc error! \n");
    	exit(0);
    }

    //add more data to linked list
    if (do_add_random_value)
	{
    	//initialization first linked list
    	first_list->data = 48+rand()%10;
    	first_list->next = NULL;
    	for (int i = 0; i < 10; i++)
    	{
    		ListAddToEnd(first_list, 48+rand()%10);
    	}
	}
    else
    {
    	char newitem[15]={};
    	printf(" Enter item to be insert: ");
    	scanf("%s", newitem);

    	//initialization first linked list
    	first_list->data = newitem[0];
    	first_list->next = NULL;
    	int i = 1;
    	while(newitem[i]!='\0' )
    	{
    		ListAddToEnd(first_list, newitem[i]);
    		i++;
    	}
    }

    //check if functions work is correct
    DisplayingLinkedList(first_list);
	ListIs(first_list, '7');
	for (int i = 0; i < 11; i++)
	{
		ListRemoveFromEnd(first_list);
		DisplayingLinkedList(first_list);
	}

//    DynamicMemoryFREE(first_list);
    free(first_list);


    printf("\n Have a good day :) \n Work was finished.");
    return 0;
}




