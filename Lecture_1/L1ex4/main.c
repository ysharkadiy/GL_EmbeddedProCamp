/*
 * main.c
 *
 *  Created on: Nov 14, 2019
 *      Author: YS
 *
 *      Ex4: Write a C program to compute the perimeter and area of
 *      a circle with a radius of 6 meters.
 */
#include <stdio.h>
#include <math.h>

int main(void)
{
	// initialization of variable
	float r = 6, perimeter, area;

	printf(" Ex.4. Calculate perimeter and area of a circle. \n");
	// calculate perimeter and area of rectangle
	perimeter = 2 * M_PI * r;
	area = M_PI * pow(r,2);
	// print out results
	printf(" Calculated perimeter %.2f and area %.2f (in meters) \n", perimeter, area);

	printf(" Have a good day :) \n Work was finished.");
	return 0;
}
