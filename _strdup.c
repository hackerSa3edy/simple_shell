#include "main.h"

/**
 * _strdup - returns a pointer to anewly allocated space in memory,
 * which contains a copy of the string given as parameter.
 *
 * @string: string to be copied.
 *
 * Return: pointer to the newly allocated space in memory, or NULL
 * in some conditions.
 */
char *_strdup(char *string)
{
	unsigned int index, size;
	char *ptr;

	if (string == NULL)
		return (NULL);

	for (size = 0; string[size];)
		size++;

	ptr = malloc((size + 1) * sizeof(char));

	if (ptr == NULL)
		return (NULL);

	for (index = 0; index <= size; index++)
		ptr[index] = string[index];

	return (ptr);
}
