#include "main.h"

/**
 * _strcat - Concatenates two strings.
 *
 * @dest: destination var.
 * @src: source buffer.
 *
 * Return: Pointer to the resulting string dest.
 */
char *_strcat(char *dest, char *src)
{
	int i1, i2;

	i1 = i2 = 0;
	while (dest[i1] != '\0')
	{
		i1++;
	}
	while (src[i2] != '\0')
	{
		dest[i1] = src[i2];
		i1++;
		i2++;
	}
	dest[i1] = src[i2];
	return (dest);
}
