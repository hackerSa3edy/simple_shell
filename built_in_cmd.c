#include "main.h"

/**
 * built_in - checks whether the command is build int command or not.
 *
 * @cmd: command.
 *
 * Return: pointer to function.
*/
int (*built_in(char *cmd))(Commands *, int *, char *, char *)
{
	built_in_t commands[] = {
		{"env", _env},
		{"exit", ___exit},
		{NULL, NULL}
	};
	int index;

	index = 0;
	while (commands[index].cmd != NULL)
	{
		if (_strcmp(cmd, commands[index].cmd) == 0)
			return (commands[index].func);
		index++;
	}
	return (NULL);
}
