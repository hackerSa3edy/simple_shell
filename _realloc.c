#include "main.h"

/**
 * _memcpy - copies memory area.
 *
 * @dest: destination location.
 * @src: source location.
 * @size: size of buffer to be copied.
 *
 * Return: pointer to dest.
 */
char *_memcpy(char *dest, char *src, unsigned int size)
{
	unsigned int index;

	for (index = 0; index < size; index++)
	{
		dest[index] = src[index];
	}
	return (dest);
}
/**
 * _realloc - reallocates a memory block using malloc and free.
 *
 * @ptr: old memory location.
 * @old_size: old size of the buffer.
 * @new_size: new size of the allocated memory.
 *
 * Return: pointer to the new allocated memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size > old_size)
	{
		new_ptr = malloc(new_size);
		_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}

	return (new_ptr);
}
