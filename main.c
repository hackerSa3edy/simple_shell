#include "main.h"

/**
 * main - main shell handler.
 *
 * @argc: number of arguments.
 * @argv: arguments' value.
 *
 * Return: (0) always success, (EXIT_CODE) otherwise.
 */
int main(int argc, char **argv)
{
	char *buffer = NULL;
	size_t bufferSize = 0;
	ssize_t bufferLen = 0;
	int lastSignal = 0, commandNumber = 0;
	int interactiveMode = isatty(STDIN_FILENO);
	Commands *commands = NULL;

	if (argc > 1)
	{
		execFile(argv, &lastSignal);
	}
	else
	{
		signal(SIGINT, SIGINT_handler);
		do {
			if (interactiveMode)
			{
				write(STDOUT_FILENO, "($) ", 4);
				fflush(NULL);
			}

			bufferLen = getline(&buffer, &bufferSize, stdin);
			if (bufferLen == -1)
			{
				free(buffer);
				if (interactiveMode)
					write(STDOUT_FILENO, "\n", 1);
				exit(lastSignal);
			}
			commands = parser(buffer);

			commandNumber++;
			execMe(commands, &lastSignal, commandNumber, argv[0], buffer);
			free_commands(commands);
		} while (interactiveMode || bufferLen != -1);
		free(buffer);
	}

	return (lastSignal);
}
