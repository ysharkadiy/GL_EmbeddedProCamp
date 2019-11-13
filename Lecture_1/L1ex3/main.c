/*
 * main.c
 *
 *  Created on: Nov 14, 2019
 *      Author: YS
 *
 *  Ex3: Write program that get from user height and weight
 *      of rectangle (in meters) and calculate perimeter and area (in inches).
 *
 */
#include <stdio.h>

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// initialization of variable
	float height, weight, perimeter, area;

	printf(" EX.3. Calculate perimeter and area of rectangle. \n");
	printf(" Enter height of rectangle (in meters) : ");
	scanf("%f", &height);
	height = height / 0.0254;

	printf(" Enter weight of rectangle (in meters) : ");
	scanf("%f", &weight);
	weight = weight / 0.0254;

	perimeter = 2 * (height + weight);
	area = height * weight;

	printf(" Calculated perimeter %.2f and area %.2f (in inches) \n", perimeter, area);

	printf(" Have a good day :) \n Work was finished.");
	return 0;
}
