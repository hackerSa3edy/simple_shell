#include "main.h"

/**
 * _setenv - set environment variable.
 *
 * @CMD: the command that the user type.
 * @lastSignal: last signal from executed functions.
 * @cmdNum: the executed command number.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: (0) always success, (1) otherwise.
*/
int _setenv(Commands *CMD, int *lastSignal, int cmdNum,
		char *programName, char *buffer)
{
	(void) lastSignal, (void) cmdNum, (void) programName, (void) buffer;
	if (CMD->cmd[1] == NULL || CMD->cmd[2] == NULL)
		return (EXIT_SUCCESS);

	setenv(CMD->cmd[1], CMD->cmd[2], 1);
	return (EXIT_SUCCESS);
}
