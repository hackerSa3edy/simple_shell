#include "main.h"

/**
 * execMe - handles the execution of the  commands.
 *
 * @commands: Commands single list to executes its commands.
 * @lastSignal: the signal by syscall.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: lastSignal
*/
void execMe(Commands *commands, int *lastSignal,
		char *programName, char *buffer)
{
	Commands *cmdExec = commands;
	int firstCMD = 1, opStatus = 0;
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
 * @logicalOp: the current logical operator.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: Nothing.
 */
void executeCommand(Commands *cmdExec, int *lastSignal,
		int *firstCMD, char *logicalOp, char *programName, char *buffer)
{
	char *command_path = NULL;

	if (cmdExec->cmd[0] != NULL)
	{
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
						perror(programName);
						*lastSignal = 127;
					}
				}
			}
		}
	}
	else
		logicalOp = NULL;
}
