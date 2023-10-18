#include "main.h"

/**
 * _strlen - return the length of a string.
 *
 * @s: string.
 *
 * Return: length of the string.
 */
int _strlen(char *s)
{
	char *ptr;
	int size = 0;

	ptr = s;
	while (*ptr != '\0')
	{
		size = sizeof(*ptr) + size;
		ptr = ptr + 1;
	}
	return (size);
}
