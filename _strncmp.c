#include "main.h"

/**
 * _strncmp - compares n characters of two strings .
 *
 * @s1: string no 1.
 * @s2: string no 2.
 * @n: number of characters to be compared.
 *
 * Return: positive num, zero and negative num.
 */
int _strncmp(char *s1, char *s2, int n)
{
		int index = 0, value = 0, counter = 0;

		while ((*(s1 + index) != '\0') && (*(s2 + index) != '\0') && counter < n)
		{
			if (*(s1 + index) != *(s2 + index))
			{
				value = (*(s1 + index) - *(s2 + index));
				break;
			}
			index++;
			counter++;
		}
		return (value);
}
