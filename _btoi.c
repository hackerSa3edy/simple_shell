#include "main.h"

/**
 * _btoi - converts numbers from int to string.
 *
 * @num: number to be processed.
 *
 * Return: the number in form of char *.
 */
char *_btoi(int num)
{
	int counter = 0, index, tempi, digit, base = 1, last;
	char *number;

	last = num % 10;
	counter += num_of_digits(num);
	number = malloc(sizeof(char) * counter + 1);
	if (counter > 1)
	{
		for (index = 1; index < counter; index++)
		{
			for (tempi = counter - index; tempi != 0; tempi--)
				base = base * 10;

			digit = num / (base);
			digit = digit % 10;
			number[index - 1] = digit + '0';
			base = 1;
		}
	}
	number[counter - 1] = last + '0';
	number[counter] = '\0';
	return (number);
}
