/*
 * main.c
 *
 *  Created on: Nov 14, 2019
 *      Author: YS
 *
 *      Ex2: Write function that converts RGB 888 to RGB 565.
 */
#include <stdio.h>

void RGB_888_to_565(int *r, int *g, int *b)
 {
	*r >>= 3; *r *= 5;
	*g >>= 2; *g *= 3;
	*b >>= 3; *b *= 5;
}

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
	int R, G, B;

	printf(" Ex2: Convert RGB 888 to RGB 565. \n");
	// read weight from customer
	printf(" Enter R G B numbers : ");
	scanf("%d %d %d", &R, &G, &B);
	RGB_888_to_565(&R, &G, &B);

	printf(" Converted RGB to 565 : %i \t%i \t%i\n", R, G, B);

	printf(" Have a good day :) \n Work was finished.");
	return 0;
}
