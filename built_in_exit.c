#include "main.h"

/**
 * ___exit - exits the shell.
 *
 * @CMD: Command type single list.
 * @lastSignal: last signal from executed functions.
 * @cmdNum: the executed Command number.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: (0) always success, (EXIT_CODE) otherwise.
*/
int ___exit(Commands *CMD, int *lastSignal, int cmdNum,
		char *programName, char *buffer)
{
	int argsLen, status;
	char **command = CMD->cmd;
	char *msg = ": exit: Illegal number: ", *cmdNumStr;

	for (argsLen = 0; command[argsLen];)
		argsLen++;

	fflush(NULL);
	free(buffer);
	if (argsLen > 1)
	{
		cmdNumStr = _btoi(cmdNum);
		status = _atoi(command[1]);
		if ((status == 0 && command[1][0] != '0') || status < 0)
		{
			write(STDERR_FILENO, programName, _strlen(programName));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, cmdNumStr, _strlen(cmdNumStr));
			write(STDERR_FILENO, msg, _strlen(msg));
			write(STDERR_FILENO, command[1], _strlen(command[1]));
			write(STDERR_FILENO, "\n", 1);
			status = 2;
		}
		free(cmdNumStr);
		free_commands(CMD);
		exit(status);
	}

	free_commands(CMD);
	exit(*lastSignal);
}
