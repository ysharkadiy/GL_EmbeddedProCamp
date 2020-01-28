/*
 * main.c
 *
 *  Created on: Nov 18, 2019
 *      Author: YS
 *
 *      Ex.1.Create function to copy all digits from input string to output string.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define IS_EMPTY_STR(X) ( (strlen(X)<=1)/*length check*/ || (X[0] == '\0')/*content check*/)

// declaration of functions
void copy_only_digits(char *input_str, char *output_str);

int main(void)
{
	/*
	 * The Eclipse console has buffering problems on Windows.
	 * Basically, it doesn't flush the streams when a newline is received.
	 * (Unlike a normal windows console window).
	 * So, I had added the following lines in the start of the main function:
	 */
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// initialization of variable
    char initial_string[1000] = "";
    char digital_string[1000] = "";

	printf(" Ex.1. Copy all digits from input string to output string. \n");
	// read string from customer
	printf(" Enter string: \n");
	fgets(initial_string, sizeof(initial_string), stdin);
	if (!IS_EMPTY_STR(initial_string))
	{
		puts(initial_string);
		printf(" initial_string = %d\n", strlen(initial_string));

		copy_only_digits(initial_string, digital_string);
		if (!IS_EMPTY_STR(digital_string))
		{
			puts(digital_string);
		}
		else printf(" Output digital string is empty!\n");
	}
	else printf(" Initial string is empty!\n");

	printf(" Have a good day :) \n Work was finished.");
	return 0;
}

// body of function that is declared before
void copy_only_digits(char *input_str, char *output_str)
{
	//used uint8_t for better control the length of str
	uint8_t input_str_length = 0;
	uint8_t output_str_index = 0;

	input_str_length = strlen(input_str);

	for (int i = 0; i < input_str_length; i++)
	{
		if (input_str[i] >= '0' && input_str[i] <= '9')
		{
			output_str[output_str_index] = input_str[i];
			output_str_index++;
		}
	}
}




