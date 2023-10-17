#include "main.h"

/**
 * _env - prints the environment variables.
 *
 * @command: the command that the user type.
 * @envp: array of all environment variables.
 *
 * Return: (0) always success, (1) otherwise.
*/
int _env(__attribute__((unused)) Commands *command, char **envp)
{
	size_t index, stringLen;

	for (index = 0; envp[index] != NULL; index++)
	{
		stringLen = _strlen(envp[index]);
		write(STDOUT_FILENO, envp[index], stringLen);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
