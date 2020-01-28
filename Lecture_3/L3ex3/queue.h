/*
 * queue.h
 *
 *  Created on: Nov 24, 2019
 *      Author: YS
 *
 *  Ex.3. Create queue library based on array:
 *      -int Put(int);          // add element
 *      -int Get(*int);         // read element and remove from queue
 *      -Int Read(*int);        // read element without removing it from queue
 */

#ifndef QUEUE_H_
#define QUEUE_H_

/**
 * initQueue() - Create empty element of queue.
 */
void initQueue();

/**
 * putQueue() - Add element to end of queue.
 * @value: Element that will be add to Queue..
 */
void putQueue(int value);

/**
 * getQueue() - Remove element from front of queue.
 *
 * Return: int value from Queue.
 */
int getQueue();

/**
 * displayQueue() - Print all elements from queue.
 */
void displayQueue();

/**
 * IsEmpty() - Check if queue is empty.
 *
 * Return: status -
 * 			if status == 0, stack is not empty.
 * 			if status == 1, stack is empty.
 */
int IsEmpty();

/**
 * IsFull() - Check if queue is full.
 * 			  This function look through all stack and count all elements.
 * 			  As default number of stack is used 10, that define MAX_STECK_ELEMENTS 10.
 *
 * Return: status -
 * 			if status == 0, stack is not full.
 * 			if status == 1, stack is full.
 */
int IsFull();

/**
 * readQueue() - Get the value of the front of queue without removing it.
 *
 * Return: int value from Queue.
 */
int readQueue();

#endif /* QUEUE_H_ */
