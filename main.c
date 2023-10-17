#include "main.h"

/**
 * main - main shell handler.
 *
 * @argc: number of arguments.
 * @argv: arguments' value.
 * @envp: environment variables.
 *
 * Return: (0) always success, (EXIT_CODE) otherwise.
 */
int main(int argc, char **argv, char **envp)
{
	char *buffer = NULL;
	size_t bufferSize;
	ssize_t bufferLen;
	int lastSignal = 0;
	int interactiveMode = isatty(STDIN_FILENO);
	Commands *commands = NULL;

	(void) argc;
	(void) argv;
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
			write(STDERR_FILENO, "\n", 1);
			free(buffer);
			exit(lastSignal);
		}
		commands = parser(buffer, bufferLen);

		execMe(commands, envp, &lastSignal);
		free_commands(commands);
	} while (interactiveMode);
	free(buffer);

	return (lastSignal);
}
