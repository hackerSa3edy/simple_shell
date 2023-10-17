#include <limits.h>

/**
 * _isdigit - checks for a digit (0 through 9).
 *
 * @c: char to be checked
 *
 * Return: 1 if @c is digit, 0 otherwise
 */
int _isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _atoi - convert a string to an integer.
 *
 * @s: string to be converted.
 *
 * Return: the converted number.
 */
int _atoi(char *s)
{
	char *ptr;
	int size, sign, for_counter, num_size, prev, cur;

	size = prev = 0;
	sign = 1;
	ptr = s;
	while (*ptr != '\0')
	{
		if (*ptr == '-')
		{
			sign = sign * -1;
			ptr = ptr + 1;
			continue;
		}

		if (_isdigit(*ptr))
		{
			if ((*(ptr + 1) == ' ') || (*(ptr + 1) == '\0'))
			{
				num_size = size;
				for (for_counter = 0; for_counter <= size; for_counter++)
				{
					cur = *(ptr - num_size) - '0';
					if ((prev > (INT_MAX / 10)) || ((INT_MAX - (prev * 10)) < cur))
					{
						return (sign == 1 ? INT_MAX : INT_MIN);
					}
					prev = prev * 10 + cur;
					num_size--;
				}
				return (prev * sign);
			}
			size = size + 1;
		}
		ptr = ptr + 1;
	}
	return (0);
}
