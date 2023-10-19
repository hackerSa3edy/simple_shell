#include "main.h"

/**
 * commandExists - checks if the command exists in the PATH or not.
 *
 * @cmd: command.
 *
 * Return: if command exists, returns the Path to the command, otherwise NULL.
*/
char *commandExists(char *cmd)
{
	char **path = _getenv("PATH");
	int index;
	char *command, *commandPath, *commandFound = NULL;

	if (path == NULL)
		return (NULL);
	command = _strdup("/");
	command = _realloc(command, _strlen(command) + 1,
			_strlen(command) + _strlen(cmd) + 1);
	command = _strcat(command, cmd);

	for (index = 0; path[index] != NULL; index++)
	{
		commandPath = _strdup(path[index]);
		commandPath = _realloc(commandPath, _strlen(commandPath) + 1,
				_strlen(command) + _strlen(path[index]) + 1);
		commandPath = _strcat(commandPath, command);
		if (access(commandPath, F_OK) == 0)
		{
			commandFound = commandPath;
			break;
		}
		free(commandPath);
	}
	free(command);

	for (index = 0; path[index] != NULL;)
		index++;

	free_2D(path, index);

	return (commandFound);
}

/**
 * doExec - checks if the command should be executed or not.
 *
 * @lastSignal: last status code from executed functions.
 * @operator: logical operator in for the previous command.
 *
 * Return: (0) don't execute, (1) otherwise.
 */
int doExec(int *lastSignal, char *operator)
{
	int exec = 0;

	if (operator == NULL || _strcmp(operator, ";") == 0)
		exec = 1;
	else if (_strcmp(operator, "&&") == 0 && *lastSignal == 0)
		exec = 1;
	else if (_strcmp(operator, "||")  == 0 && *lastSignal != 0)
		exec = 1;

	return (exec);
}

/**
 * execAbsolutePath - executes a command which the user has provided its path.
 *
 * @cmdExec: commands as Commands type single list.
 * @lastSignal: last status code from functions.
 * @programName: the name of the running executable.
 * @buffer: the original buffer from getline function.
 *
 * Return: Nothing.
 */
void execAbsolutePath(Commands *cmdExec, int *lastSignal,
		char *programName, char *buffer)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		perror("fork error - absolute path");
	else if (pid == 0)
	{
		status = execve(cmdExec->cmd[0], cmdExec->cmd, environ);
		if (status == -1)
			perror(programName);

		free(buffer);
		free_commands(cmdExec);
		_exit(EXIT_FAILURE);
	}
	else
	{
		wait(lastSignal);
		*lastSignal = WEXITSTATUS(*lastSignal);
	}
}

/**
 * execCommandPath - executes a command from PATH.
 *
 * @cmdExec: commands as Commands type single list.
 * @lastSignal: last status code from functions.
 * @command_path: the command path.
 * @programName: the name of the running executable.
 * @buffer: the original buffer from getline function.
 *
 * Return: Nothing.
 */
void execCommandPath(Commands *cmdExec, int *lastSignal,
		char *command_path, char *programName, char *buffer)
{
	pid_t pid;
	int execStatus;

	pid = fork();
	if (pid == -1)
		perror("fork error - command path");
	else if (pid == 0)
	{
		if (access(command_path, X_OK) == 0)
		{
			execStatus = execve(command_path, cmdExec->cmd, environ);
			if (execStatus == -1)
				perror(programName);
		}
		else
			perror(programName);

		free_commands(cmdExec);
		fflush(NULL);
		free(buffer);
		free(command_path);
		_exit(EXIT_FAILURE);
	}
	else
	{
		free(command_path);
		wait(lastSignal);
		*lastSignal = WEXITSTATUS(*lastSignal);
	}
}
