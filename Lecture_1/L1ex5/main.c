/*
 * main.c
 *
 *  Created on: Nov 14, 2019
 *      Author: YS
 *
 *      Ex5: Write a C program to compute factorial of 10.
 */
#include <stdio.h>

// body of function without declaration
int factorial(int x)
{
	int f_value = 1;
	while(x>0)
	{
		f_value *= x;
		x --;
	}
	return f_value;
}
// second method for factorial calculation
int fact(int x)
{
	if(x > 1)
	{
		return x*fact(x-1);
	}
	else
	{
		return x;
	}
}

int main(void)
{
	// initialization of variable
	int test_value = 10, f_result = 1;

	printf(" Ex5: Write a C program to compute factorial of 10. \n");
	// compute factorial of 10 by function and print out result
	printf(" Factorial of 10 = %d \n", factorial(test_value));
	printf(" Second method = %d \n", fact(test_value));
	// third method
	for(int i = 1; i <= test_value; i++)
	{
		f_result *= i;
	}
	printf(" Third method = %d \n", f_result);
	printf(" Have a good day :) \n Work was finished.");
	return 0;
}
