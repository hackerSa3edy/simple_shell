#include "main.h"

/**
 * execMe - handles the execution of the  commands.
 *
 * @commands: Commands single list to executes its commands.
 * @lastSignal: the signal by syscall.
 * @cmdNum: the number of executed commands.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: lastSignal
*/
void execMe(Commands *commands, int *lastSignal, int cmdNum,
		char *programName, char *buffer)
{
	Commands *cmdExec = commands;
	int firstCMD = 1, opStatus = 0;
	char *logicalOp, *prevOp;

	if (cmdExec != NULL)
		logicalOp = prevOp = cmdExec->op;
	while (cmdExec != NULL)
	{
		executeCommand(cmdExec, lastSignal, &firstCMD, cmdNum,
				logicalOp, programName, buffer);
Here:
		if (cmdExec->op != NULL)
		{
			opStatus = 0;
			if (_strcmp(cmdExec->op, "||") == 0)
				opStatus = orOperator(&cmdExec, lastSignal, &prevOp, &logicalOp);
			else if (_strcmp(cmdExec->op, "&&") == 0)
				opStatus = andOperator(&cmdExec, lastSignal, &prevOp, &logicalOp);
			else if (_strcmp(cmdExec->op, ";") == 0)
			{
				logicalOp = cmdExec->op;
				cmdExec = cmdExec->nextCmd;
			}
			if (opStatus == GOTO)
				goto Here;
		}
		else
		{
STOPME:
			if (logicalOp != NULL)
			{
				opStatus = operatorsChain(&cmdExec, lastSignal, &prevOp, &logicalOp);
				if (opStatus == GOTO)
					goto STOPME;
			}
			else
				cmdExec = cmdExec->nextCmd;
		}
	firstCMD = 0;
	}
}
/**
 * executeCommand - executes commands.
 *
 * @cmdExec: Commands single list to executes its commands.
 * @lastSignal: the signal by syscall.
 * @firstCMD: (1) indicates this command is first command, (0) otherwise.
 * @cmdNum: the number of executed commands.
 * @logicalOp: the current logical operator.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: Nothing.
 */
void executeCommand(Commands *cmdExec, int *lastSignal,
		int *firstCMD, int cmdNum, char *logicalOp,
		char *programName, char *buffer)
{
	char *command_path = NULL;

	if (cmdExec->cmd[0] != NULL)
	{
		if (built_in(cmdExec->cmd[0]))
		{
			if (doExec(lastSignal, logicalOp) || firstCMD)
				*lastSignal = built_in(cmdExec->cmd[0])(cmdExec,
						lastSignal, cmdNum, programName, buffer);
		}

		else
		{
			if (absolutePath(cmdExec->cmd[0]))
			{
				if (doExec(lastSignal, logicalOp) || firstCMD)
					execAbsolutePath(cmdExec, lastSignal, programName, buffer);
			}

			else
			{
				if (doExec(lastSignal, logicalOp) || firstCMD)
				{
					command_path = commandExists(cmdExec->cmd[0]);
					if (command_path != NULL)
						execCommandPath(cmdExec, lastSignal, command_path, programName, buffer);

					else
					{
						print_notFoundErr(programName, cmdNum, cmdExec->cmd[0]);
						*lastSignal = 127;
					}
				}
			}
		}
	}
	else
		logicalOp = NULL;
}

/**
 * print_notFoundErr - prints the 127 status code error msg.
 *
 * @programName: the current executable program name.
 * @cmdNum: number of the command.
 * @command: the command which didn't find in PATH.
 *
 * Return: Nothing.
 */
void print_notFoundErr(char *programName, int cmdNum, char *command)
{
	char *numberInString, *msg = ": not found\n";

	numberInString = _btoi(cmdNum);
	write(STDERR_FILENO, programName, _strlen(programName));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, numberInString, _strlen(numberInString));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, msg, _strlen(msg));

	free(numberInString);
}
