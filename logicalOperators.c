#include "main.h"

/**
 * orOperator - handles || logical operator.
 *
 * @cmdExec: Commands single list to executes its commands.
 * @lastSignal: the signal by syscall.
 * @prevOp: previous logical operator.
 * @logicalOp: current logical operator.
 *
 * Return: (GOTO) macro, or (0).
 */
int orOperator(Commands **cmdExec, int *lastSignal,
		char **prevOp, char **logicalOp)
{
	if (*lastSignal == 0)
	{
		if (((*cmdExec)->nextCmd)->nextCmd != NULL && (*cmdExec)->nextCmd != NULL)
		{
			*prevOp = (*cmdExec)->op;
			*cmdExec = (*cmdExec)->nextCmd;
			*logicalOp = (*cmdExec)->op;
			*cmdExec = (*cmdExec)->nextCmd;
			return (GOTO);
		}
		else
		{
			*prevOp = (*cmdExec)->op;
			*cmdExec = (*cmdExec)->nextCmd;
			*logicalOp = (*cmdExec)->op;
			return (GOTO);
		}
	}
	else
	{
		*prevOp = *logicalOp;
		*logicalOp = (*cmdExec)->op;
		*cmdExec = (*cmdExec)->nextCmd;
	}
	return (0);
}

/**
 * andOperator - handles && logical operator.
 *
 * @cmdExec: Commands single list to executes its commands.
 * @lastSignal: the signal by syscall.
 * @prevOp: previous logical operator.
 * @logicalOp: current logical operator.
 *
 * Return: (GOTO) macro, or (0).
 */
int andOperator(Commands **cmdExec, int *lastSignal,
		char **prevOp, char **logicalOp)
{
	if (*lastSignal == 0)
	{
		*prevOp = *logicalOp;
		*logicalOp = (*cmdExec)->op;
		*cmdExec = (*cmdExec)->nextCmd;
	}
	else
	{
		if (((*cmdExec)->nextCmd)->nextCmd != NULL && (*cmdExec)->nextCmd != NULL)
		{
			*prevOp = (*cmdExec)->op;
			*cmdExec = (*cmdExec)->nextCmd;
			*logicalOp = (*cmdExec)->op;
			*cmdExec = (*cmdExec)->nextCmd;
			return (GOTO);
		}
		else
		{
			*prevOp = (*cmdExec)->op;
			*cmdExec = (*cmdExec)->nextCmd;
			*logicalOp = (*cmdExec)->op;
			return (GOTO);
		}
	}
	return (0);
}

/**
 * operatorsChain - handles chain of logical operator.
 *
 * @cmdExec: Commands single list to executes its commands.
 * @lastSignal: the signal by syscall.
 * @prevOp: previous logical operator.
 * @logicalOp: current logical operator.
 *
 * Return: (GOTO) macro, or (0).
 */
int operatorsChain(Commands **cmdExec, int *lastSignal,
		char **prevOp, char **logicalOp)
{
	if (_strcmp(*logicalOp, "&&") == 0)
	{
		if (*lastSignal != 0)
			*cmdExec = (*cmdExec)->nextCmd;
		else if (*lastSignal == 0 && (_strcmp(*prevOp, ";") == 0
					|| _strcmp(*prevOp, "||") == 0))
			*cmdExec = (*cmdExec)->nextCmd;
		else
		{
			*logicalOp = (*cmdExec)->op;
			return (GOTO);
		}
	}
	else if (_strcmp(*logicalOp, "||") == 0)
	{
		if (*lastSignal == 0)
			*cmdExec = (*cmdExec)->nextCmd;
		else if (*lastSignal != 0 && (_strcmp(*prevOp, ";") == 0
					|| _strcmp(*prevOp, "&&") == 0))
		{
			*logicalOp = (*cmdExec)->op;
		}
		else
		{
			*logicalOp = (*cmdExec)->op;
			return (GOTO);
		}
	}
	else if (_strcmp(*logicalOp, ";") == 0)
		*cmdExec = (*cmdExec)->nextCmd;
	else
	{
		*logicalOp = (*cmdExec)->op;
		return (GOTO);
	}

	return (0);
}
