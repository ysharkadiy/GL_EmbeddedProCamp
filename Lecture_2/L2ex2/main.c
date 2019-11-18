/*
 * main.c
 *
 *  Created on: Nov 18, 2019
 *      Author: YS
 *
 *      Ex.2.Create function to find the biggest element in integer array.
 */
#include <stdio.h>
#include <stdlib.h>

int find_bigest_el(int arr_s, int *data_ptr)
{
	int max = 0;
	// Loop to store largest number at address data
	for(int i = 0; i < arr_s; i++)
	{
		// Change "<" to ">" if you want to find the smallest number
		if(max < *(data_ptr + i))
		{
			max = *(data_ptr + i);
		}
	}
	return max;
}

void fill_array(int arr_s, int *data_ptr)
{
	// Stores the number entered by the user or random.
	for(int i = 0; i < arr_s; i++)
	{
		//printf("Enter Number %d: ", i + 1);
		//scanf("%d", data + i);
		*(data_ptr+i) = rand();
		printf("%d, ", *(data_ptr+i));
	}
}

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
	int array_size, *data, max_value = 0;

    printf(" Ex.2. Find the biggest element. \n");
    printf(" Enter total number of elements: ");
    scanf("%d", &array_size);

    // Allocates the memory for 'array_size' elements.
    data = (int*)calloc(array_size, sizeof(int));
    if(data == NULL)
    {
    	printf(" Error!!! Memory not allocated.");
    	exit(0);
    }
    printf("\n");

    fill_array(array_size, data);
    max_value = find_bigest_el(array_size, data);

    printf("\n Largest element = %d \n", max_value);
    free(data);


    printf(" Have a good day :) \n Work was finished.");
    return 0;
}




