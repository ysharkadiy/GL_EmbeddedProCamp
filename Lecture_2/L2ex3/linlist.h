/*
 * linlist.h
 *
 *  Created on: Nov 18, 2019
 *      Author: YS
 */

#ifndef LINLIST_H_
#define LINLIST_H_
/*
 * Linked list library with functions (ListAdd(), ListIs(), ListRemove()).
 * New elements in list is dynamically allocate.
 */

typedef struct LinkedList
{
    char data;
    struct LinkedList *next;
} LinList;

/*
 * function ListAddToEnd: adding new item in the end of the list.
 */
void ListAddToEnd(LinList *head, char newValue);

/*
 * function ListIs: finding item in the list.
 * If item is in the list, function returns his index in the list.
 * If not function returns message.
 */
void ListIs(LinList *head, char data);

/*
 * function ListRemoveFromEnd: remove last items in the list.
 */
void ListRemoveFromEnd(LinList *head);

/*
 * function DisplayingLinkedList: display all elements from linked list.
 */
void DisplayingLinkedList(LinList *head);

/*
 * function DynamicMemoryFREE: free all pointers in List
 */
void DynamicMemoryFREE(LinList *head);

#endif /* LINLIST_H_ */
