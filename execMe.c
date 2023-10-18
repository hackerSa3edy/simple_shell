#include "main.h"

/**
 * execMe - executes commands.
 *
 * @commands: Commands single list to executes its commands.
 * @lastSignal: the signal by syscall.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: lastSignal
*/
int execMe(Commands *commands, int *lastSignal,
		char *programName, char *buffer)
{
	Commands *cmdExec = commands;
	int firstCMD = 1, index = 0;
	char *logicalOp, *prevOp;

	if (cmdExec != NULL)
		logicalOp = prevOp = cmdExec->op;
	while (cmdExec != NULL)
	{
		executeCommand(cmdExec, lastSignal, &firstCMD,
				logicalOp, programName, buffer);
Here:
		if (cmdExec->op != NULL)
		{
			if (_strcmp(cmdExec->op, "||") == 0)
			{
				if (*lastSignal == 0)
				{
					if ((cmdExec->nextCmd)->nextCmd != NULL && cmdExec->nextCmd != NULL)
					{
						prevOp = cmdExec->op;
						cmdExec = cmdExec->nextCmd;
						logicalOp = cmdExec->op;
						cmdExec = cmdExec->nextCmd;
						goto Here;
					}
					else
					{
						prevOp = cmdExec->op;
						cmdExec = cmdExec->nextCmd;
						logicalOp = cmdExec->op;
						goto Here;
					}
				}
				else
				{
					prevOp = logicalOp;
					logicalOp = cmdExec->op;
					cmdExec = cmdExec->nextCmd;
				}
			}
			else if (_strcmp(cmdExec->op, "&&") == 0)
			{
				if (*lastSignal == 0)
				{
					prevOp = logicalOp;
					logicalOp = cmdExec->op;
					cmdExec = cmdExec->nextCmd;
				}
				else
				{
					if ((cmdExec->nextCmd)->nextCmd != NULL && cmdExec->nextCmd != NULL)
					{
						prevOp = cmdExec->op;
						cmdExec = cmdExec->nextCmd;
						logicalOp = cmdExec->op;
						cmdExec = cmdExec->nextCmd;
						goto Here;
					}
					else
					{
						prevOp = cmdExec->op;
						cmdExec = cmdExec->nextCmd;
						logicalOp = cmdExec->op;
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
		{
STOPME:
			if (logicalOp != NULL)
			{
				if (_strcmp(logicalOp, "&&") == 0)
				{
					if (*lastSignal != 0)
						cmdExec = cmdExec->nextCmd;
					else if (*lastSignal == 0 && (_strcmp(prevOp, ";") == 0
								|| _strcmp(prevOp, "||") == 0))
						cmdExec = cmdExec->nextCmd;
					else
					{
						logicalOp = cmdExec->op;
						goto STOPME;
					}
				}
				else if (_strcmp(logicalOp, "||") == 0)
				{
					if (*lastSignal == 0)
						cmdExec = cmdExec->nextCmd;
					else if (*lastSignal != 0 && (_strcmp(prevOp, ";") == 0
								|| _strcmp(prevOp, "&&") == 0))
					{
						logicalOp = cmdExec->op;
					}
					else
					{
						logicalOp = cmdExec->op;
						goto STOPME;
					}
				}
				else if (_strcmp(logicalOp, ";") == 0)
					cmdExec = cmdExec->nextCmd;
				else
				{
					logicalOp = cmdExec->op;
					goto STOPME;
				}
			}
			else
				cmdExec = cmdExec->nextCmd;
		}
	if (index++ == 10)
		break;
	firstCMD = 0;
	}

	return (1);
}

void executeCommand(Commands *cmdExec, int *lastSignal,
		int *firstCMD, char *logicalOp, char *programName, char *buffer)
{
	char *command_path = NULL;

	if (built_in(cmdExec->cmd[0]))
	{
		if (doExec(lastSignal, logicalOp) || firstCMD)
			*lastSignal = built_in(cmdExec->cmd[0])(cmdExec,
					lastSignal, programName, buffer);
	}

	else
	{
		if (absolutePath(cmdExec->cmd[0]))
		{
			if (doExec(lastSignal, logicalOp) || firstCMD)
				execAbsolutePath(cmdExec, lastSignal, buffer);
		}

		else
		{
			if (doExec(lastSignal, logicalOp) || firstCMD)
			{
				command_path = commandExists(cmdExec->cmd[0]);
				if (command_path != NULL)
					execCommandPath(cmdExec, lastSignal, command_path, buffer);

				else
				{
					perror(programName);
					*lastSignal = 127;
				}
			}
		}
	}
}

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
 * @buffer: the original buffer from getline function.
 *
 * Return: Nothing.
 */
void execAbsolutePath(Commands *cmdExec, int *lastSignal, char *buffer)
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
			perror("execve - absolute path");

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
 * @buffer: the original buffer from getline function.
 *
 * Return: Nothing.
 */
void execCommandPath(Commands *cmdExec, int *lastSignal,
		char *command_path, char *buffer)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		perror("fork error - command path");
	else if (pid == 0)
	{
		if (access(command_path, X_OK) == 0)
		{
			*lastSignal = execve(command_path, cmdExec->cmd, environ);
			if (*lastSignal == -1)
				perror("execve - command path");
		}
		else
		{
			perror("access");
			*lastSignal = -1;
		}
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
