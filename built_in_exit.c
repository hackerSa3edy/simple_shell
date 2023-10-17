#include "main.h"

/**
 * ___exit - exits the shell.
 *
 * @CMD: Command type single list.
 * @envp: array of all environment variables.
 *
 * Return: (0) always success, (EXIT_CODE) otherwise.
*/
int ___exit(Commands *CMD, char **envp)
{
	int argsLen, status;
	char **command = CMD->cmd;

	(void) envp;
	for (argsLen = 0; command[argsLen];)
		argsLen++;

	fflush(NULL);
	if (argsLen > 1)
	{
		status = _atoi(command[1]);
		free_commands(CMD);
		exit(status);
	}

	free_commands(CMD);
	exit(0);
}
