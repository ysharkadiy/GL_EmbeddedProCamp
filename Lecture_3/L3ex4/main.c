/*
 * main.c
 *
 *  Created on: Nov 23, 2019
 *      Author: YS
 *
 *      Ex.4. Create function, that receives pointer to other function as a parameter.
 */
#include <stdio.h>
#include <stdint.h>

/**
 * math() - Function, that receives pointer to other function.
 * 			Make mathematical operations: sum, div, sub, mul.
 * @ptr_to_func: Pointer to other functions.
 * @x: First argument for any mathematical operations.
 * @y: Second argument for any mathematical operations.
 *
 * Return: Result of mathematical operation of two int numbers.
 */
float math(void *ptr_to_func, int16_t x, int16_t y)
{
	float (*func)(int16_t, int16_t);
	func = ptr_to_func;
	return func(x, y);
}
/**
 * Sum() - Function, that add two int numbers.
 * @x: First argument of mathematical operation.
 * @y: Second argument of mathematical operation.
 *
 * Return: Result of adding two int numbers.
 */
float Sum(int16_t x, int16_t y)
{
	return x+y;
}
/**
 * Div() - Function, that divide two int numbers.
 * @x: First argument of mathematical operation.
 * @y: Divider.
 *
 * Return: Result of dividing two int numbers.
 */
float Div(int16_t x, int16_t y)
{
	return (float)x/y;
}
/**
 * Sub() - Function, that subtraction two int numbers.
 * @x: Source number of subtraction.
 * @y: Subtrahend.
 *
 * Return: Result of subtraction two int numbers.
 */
float Sub(int16_t x, int16_t y)
{
	return x-y;
}
/**
 * Mul() - Function, that multiply two int numbers.
 * @x: First multiplier.
 * @y: Second multiplier.
 *
 * Return: Result of multiply two int numbers.
 */
float Mul(int16_t x, int16_t y)
{
	return x*y;
}



int main()
{
	/**
	 * DOC: Theory of Operation
	 * The Eclipse console has buffering problems on Windows.
	 * Basically, it doesn't flush the streams when a newline is received.
	 * (Unlike a normal windows console window).
	 * So, I had added the following lines in the start of the main function:
	 */
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf(" Ex.4. Receive pointer to other function. \n");

	// initialization of variable
	int16_t a,b;

	printf("Entered processed values : \n");
	printf("a = ");
	scanf("%d", &a);
	printf("b = ");
	scanf("%d", &b);
	printf("Sum is %.0f \n", math(Sum, a, b));
	printf("Div is %.5f \n", math(Div, a, b));
	printf("Sub is %.0f \n", math(Sub, a, b));
	printf("Mul is %.0f \n", math(Mul, a, b));

	printf("\n Have a good day :) \n Work was finished.");
	return 0;
}
