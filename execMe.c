#include "main.h"

/**
 * execMe - executes commands.
 *
 * @commands: Commands single list to executes its commands.
 * @envp: array of environment variables.
 * @lastSignal: the signal by syscall.
 *
 * Return: lastSignal
*/
int execMe(Commands *commands, char **envp, int *lastSignal)
{
	Commands *cmdExec = commands;
	int firstCMD = 1;
	char *command_path, *logicalOp = cmdExec->op;

	while (cmdExec != NULL)
	{
		if (built_in(cmdExec->cmd[0]) && (doExec(lastSignal, logicalOp) || firstCMD))
		{
			*lastSignal = built_in(cmdExec->cmd[0])(cmdExec, envp);
			dprintf(STDOUT_FILENO, "built_int: signal: %i\n", *lastSignal);
		}
		else
		{
			if (absolutePath(cmdExec->cmd[0]) && (doExec(lastSignal, logicalOp) || firstCMD))
				execAbsolutePath(cmdExec, lastSignal, envp);

			else
			{
				if ((doExec(lastSignal, logicalOp) || firstCMD))
				{
					command_path = commandExists(cmdExec->cmd[0], envp);
					if (command_path != NULL)
						execCommandPath(cmdExec, lastSignal, envp, command_path);

					else
					{
						perror("command doesn't exist");
						*lastSignal = 127;
					}
				}
			}
		}
Here:
		if (cmdExec->op != NULL)
		{
			dprintf(STDOUT_FILENO, "execMe\n");
			if (_strcmp(cmdExec->op, "||") == 0)
			{
				if (*lastSignal == 0)
				{
					if ((cmdExec->nextCmd)->nextCmd != NULL && cmdExec->nextCmd != NULL)
					{
						logicalOp = cmdExec->op;
						cmdExec = (cmdExec->nextCmd)->nextCmd;
						goto Here;
					}
					else
					{
						cmdExec = cmdExec->nextCmd;
						goto Here;
					}
				}
				else
				{
					logicalOp = cmdExec->op;
					cmdExec = cmdExec->nextCmd;
				}
			}
			else if (_strcmp(cmdExec->op, "&&") == 0)
			{
				if (*lastSignal == 0)
				{
					logicalOp = cmdExec->op;
					cmdExec = cmdExec->nextCmd;
				}
				else
				{
					if ((cmdExec->nextCmd)->nextCmd != NULL && cmdExec->nextCmd != NULL)
					{
						logicalOp = cmdExec->op;
						cmdExec = (cmdExec->nextCmd)->nextCmd;
						goto Here;
					}
					else
					{
						cmdExec = cmdExec->nextCmd;
						goto Here;
					}
				}
			}
			else if (_strcmp(cmdExec->op, ";") == 0)
			{
				logicalOp = cmdExec->op;
				cmdExec = cmdExec->nextCmd;
			}
		}
		else
			cmdExec = cmdExec->nextCmd;

	firstCMD = 0;
	}

	return (1);
}

/**
 * commandExists - checks if the command exists in the PATH or not.
 *
 * @cmd: command.
 * @envp: environment variables.
 *
 * Return: if command exists, returns the Path to the command, otherwise NULL.
*/
char *commandExists(char *cmd, char **envp)
{
	char **path = _getenv("PATH", envp);
	int index;
	char *command, *commandPath, *commandFound = NULL;

	command = _strdup("/");
	command = _realloc(command, _strlen(command) + 1, _strlen(command) + _strlen(cmd) + 1);
	command = _strcat(command, cmd);

	for (index = 0; path[index] != NULL; index++)
	{
		commandPath = _strdup(path[index]);
		commandPath = _realloc(commandPath, _strlen(commandPath) + 1, _strlen(command) + _strlen(path[index]) + 1);
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

int doExec(int *lastSignal, char *operator)
{
	int exec = 0;

	dprintf(STDOUT_FILENO, "doExec - lastSignal: %i\n", *lastSignal);
	if (operator == NULL || _strcmp(operator, ";") == 0)
		exec = 1;
	else if (_strcmp(operator, "&&") == 0 && *lastSignal == 0)
		exec = 1;
	else if (_strcmp(operator, "||")  == 0 && *lastSignal != 0)
		exec = 1;

	return (exec);
}

void execAbsolutePath(Commands *cmdExec, int *lastSignal, char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		perror("fork error - absolute path");
	else if (pid == 0)
	{
		if (access(cmdExec->cmd[0], X_OK) == 0)
		{
			*lastSignal = execve(cmdExec->cmd[0], cmdExec->cmd, envp);
			dprintf(STDOUT_FILENO, "absolute path after access: signal: %i\n", *lastSignal);
			if (*lastSignal == -1)
				perror("execve - absolute path");
		}
		else
		{
			dprintf(STDOUT_FILENO, "absolute path 'else': signal: %i\n", *lastSignal);
			perror("access");
			*lastSignal = -1;
		}
		free_commands(cmdExec);
		fflush(NULL);
		_exit(*lastSignal);
	}
	else
	{
		wait(lastSignal);
		dprintf(STDOUT_FILENO, "absolute path: signal: %i\n", *lastSignal);
	}
}

void execCommandPath(Commands *cmdExec, int *lastSignal, char **envp, char *command_path)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		perror("fork error - command path");
	else if (pid == 0)
	{
		if (access(command_path, X_OK) == 0)
		{
			*lastSignal = execve(command_path, cmdExec->cmd, envp);
			dprintf(STDOUT_FILENO, "command path after access: signal: %i\n", *lastSignal);
			if (*lastSignal == -1)
				perror("execve - command path");
		}
		else
		{
			dprintf(STDOUT_FILENO, "command path 'else': signal: %i\n", *lastSignal);
			perror("access");
			*lastSignal = -1;
		}
		free_commands(cmdExec);
		fflush(NULL);
		free(command_path);
		_exit(*lastSignal);
	}
	else
	{
		wait(lastSignal);
		dprintf(STDOUT_FILENO, "command path: signal: %i\n", *lastSignal);
	}
}
