#include "main.h"

/**
 * _unsetenv - unset environment variable.
 *
 * @CMD: the command that the user type.
 * @lastSignal: last signal from executed functions.
 * @cmdNum: the executed command number.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: (0) always success, (1) otherwise.
*/
int _unsetenv(Commands *CMD, int *lastSignal, int cmdNum,
		char *programName, char *buffer)
{
	(void) buffer;
	(void) programName;
	(void) cmdNum;
	(void) lastSignal;
	if (CMD->cmd[1] == NULL)
		return (EXIT_SUCCESS);

	unsetenv(CMD->cmd[1]);
	return (EXIT_SUCCESS);
}
