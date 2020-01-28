/*
 * main.c
 *
 *  Created on: Nov 23, 2019
 *      Author: YS
 *
 *      Ex.1. Create void function that copies one string to another.
 */
#include <stdio.h>
#include <string.h>

#define IS_EMPTY_STR(X) ( (strlen(X)<1)/*length check*/ || (X[0] == '\0')/*content check*/)

/**
 * copy_str() - Copies one string to another.
 * @soursestr_ptr: Pointer to source string for coping.
 * @newstr_ptr: Pointer to new string that contain source string.
 *
 * Return:
 */
void copy_str(char *soursestr_ptr, char *newstr_ptr)
{
	strcpy(newstr_ptr, soursestr_ptr);
	/*
	 * Also could be used:
	 * newstr_ptr = soursestr_ptr;
	 *
	 * Like change point address for new string. It could take less memory allocation for this operation.
	 */
}

/**
 * function main(): Main function that finished 0. No input arguments.
 */
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
	printf(" Ex.1. Copies one string to another. \n");

	// initialization of variable
	char first_str[1000], second_str[1000];
	printf(" Please keep in mind that string should have init length [%d]. \n", strlen(first_str));

    printf(" Enter String to coping = ");
    fgets(first_str, sizeof(first_str), stdin);
//    gets(first_str);
	if IS_EMPTY_STR(first_str)
		printf(" Input string is empty. \n");
	else
	{
		copy_str(first_str, second_str);
		printf(" Result of copying : %s\n", second_str); // could be used puts() or fputs()
	}

	printf(" Have a good day :) \n Work was finished.");
	return 0;
}





