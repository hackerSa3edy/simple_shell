#include "main.h"

/**
 * _env - prints the environment variables.
 *
 * @command: the command that the user type.
 * @lastSignal: last signal from executed functions.
 * @cmdNum: the executed command number.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: (0) always success, (1) otherwise.
*/
int _env(__attribute__((unused)) Commands * command,
		int *lastSignal, int cmdNum, char *programName, char *buffer)
{
	size_t index, stringLen;

	(void) lastSignal;
	(void) buffer;
	(void) programName;
	(void) cmdNum;
	for (index = 0; environ[index] != NULL; index++)
	{
		stringLen = _strlen(environ[index]);
		write(STDOUT_FILENO, environ[index], stringLen);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
