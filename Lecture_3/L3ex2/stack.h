/*
 * stack.h
 *
 *
 * Create stack library based on linked list:
 *      -int Push(int);    // add element
 *      -int Pop(*int);    // read element and remove from stack
 *      -int Read(*int);   // read element without removing it from stack
 *
 *  Created on: Nov 24, 2019
 *      Author: YS
 */
#ifndef STACK_H_
#define STACK_H_

/**
 * struct node - It's structure with int data that looks like Linked List.
 * 				Could be used for realization of Stack, Queues, Linked List, etc.
 * 				Keep in mind: *head* points to the first node of the linked list
 * @data: int data.
 * @*next: Pointer to next element of Linked List(Stack, etc.).
 * 		   Next pointer of last node is NULL, so if next of current node is NULL, we have reached end of linked list.
 *
 */
struct node
{
    int data;
    struct node *next;
};
 /**
  * typedef stack_t - Define type of Stack.
  */
typedef struct node stack_t;

/**
 * Push() - Add element to top of stack.
 * 			This function changes the position of head
 * 			pointer so is needed to pass the address of head
 * 			pointer and change its value within the function.
 *
 * 			Also this function check if stack (heap) is full. Then inserting an element would
 *			lead to stack overflow. If stack overflow, memory will be free and program will be finished with code 1.
 *
 * @**topRef: Pointer to current element on stack.
 * 			Also, notice how we pass address of head as struct node
 * 			**topRef in the functions Push and Pop.
 * 			These two functions change the position of head pointer so we need
 * 			to pass the address of head pointer and change its value within the function.
 */
void Push(stack_t **topRef, int newValue);

/**
 * IsEmpty() - Check if stack is empty.
 * @*top: Pointer to current element on stack.
 *
 * Return: status -
 * 			if status == 0, stack is not empty.
 * 			if status == 1, stack is empty.
 */
int IsEmpty(stack_t *top);

/**
 * IsFull() - Check if stack is full.
 * 			  This function look through all stack and count all elements.
 * 			  As default number of stack is used 10, that define MAX_STECK_ELEMENTS 10.
 * @*top: Pointer to current element on stack.
 *
 * Return: status -
 * 			if status == 0, stack is not full.
 * 			if status == 1, stack is full.
 */
int IsFull(stack_t *top);

/**
 * Read() - Get the value of the top element without removing it.
 * 			Also called as Peek.
 * @*top: Pointer to current element on stack.
 *
 * Return: int data from top of stack.
 */
int Read(stack_t *top);

/**
 * Pop() - Remove element from top of stack.
 * 			This function changes the position of head
 * 			pointer so is needed to pass the address of head
 * 			pointer and change its value within the function.
 * @**topRef: Pointer to current element on stack.
 * 			Also, notice how we pass address of head as struct node
 * 			**topRef in the functions Push and Pop.
 * 			These two functions change the position of head pointer so we need
 * 			to pass the address of head pointer and change its value within the function.
 *
 *  Return: int data wich was removed from top of stack.
 */
int Pop(stack_t **topRef);

/**
 * DisplayingLinkedList() - Print all elements from stack.
 * @*top: Pointer to Top of current stack.
 */
void DisplayingStack(stack_t *top);

/**
 * DynamicMemoryFREE() - Free all pointers in Linked List or stack.
 * @*top: Pointer to Top of current stack.
 */
void DynamicMemoryFREE(stack_t *top);

#endif /* STACK_H_ */
