/*
 * main.c
 *
 *  Created on: Nov 14, 2019
 *      Author: YS
 */
#include <stdio.h>

int main(void) {
	/*
	 * The Eclipse console has buffering problems on Windows.
	 * Basically, it doesn't flush the streams when a newline is received.
	 * (Unlike a normal windows console window).
	 * So, I had added the following lines in the start of the main function:
	 */
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// initialization of variable
	float height, weight, perimeter, area;

	printf(" EX.3. Calculate perimeter and area of rectangle. \n\n");

	// read height from customer
	printf(" Enter height of rectangle (in meters) : ");
	scanf("%f", &height);
	height = height / 0.0254;

	// read weight from customer
	printf(" Enter weight of rectangle (in meters) : ");
	scanf("%f", &weight);
	weight = weight / 0.0254;

	// calculate perimeter and area of rectangle
	perimeter = 2 * (height + weight);
	area = height * weight;
	// print out results
	printf(" Calculated perimeter %.2f and area %.2f (in inches) \n", perimeter, area);

	printf(" Have a good day :) \n Work was finished.");
	return 0;
}
