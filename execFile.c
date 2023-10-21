#include "main.h"

/**
 * execFile - executes commands from file.
 *
 * @arguments: user input.
 * @lastSignal: last status for the final executed command.
 *
 * Return: Nothing.
 */
void execFile(char **arguments, int *lastSignal)
{
	int commandNumber = 0;
	char *progName = arguments[0], *file = arguments[1];
	char *buffer = NULL;
	size_t size = 0;
	ssize_t readBytes = 0;
	Commands *commands;
	FILE *fd;

	fd = fopen(file, "r");
	if (fd == NULL)
	{
		write(STDERR_FILENO, progName, _strlen(progName));
		write(STDERR_FILENO, ": 0: Can't open ", 16);
		write(STDERR_FILENO, file, _strlen(file));
		write(STDERR_FILENO, "\n", 1);
		exit(127);
	}

	while (readBytes != -1)
	{
		readBytes = getline(&buffer, &size, fd);
		if (readBytes == -1)
		{
			free(buffer);
			fclose(fd);
			return;
		}

		commands = parser(buffer);

		commandNumber++;
		execMe(commands, lastSignal, commandNumber, progName, buffer);
		free_commands(commands);
	}
}
