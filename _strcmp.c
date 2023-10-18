#include "main.h"

/**
 * _strcmp - compares two strings.
 *
 * @s1: string no 1.
 * @s2: string no 2.
 *
 * Return: positive num, zero and negative num.
 */
int _strcmp(char *s1, char *s2)
{
		int index = 0;
		int value = 0;

		while ((*(s1 + index) != '\0') && (*(s2 + index) != '\0'))
		{
			if (*(s1 + index) != *(s2 + index))
			{
				value = (*(s1 + index) - *(s2 + index));
				break;
			}
			index++;
		}
		return (value);
}
