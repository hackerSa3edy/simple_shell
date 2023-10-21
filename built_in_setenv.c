#include "main.h"

/**
 * _setenv - set environment variable.
 *
 * @CMD: the command that the user type.
 * @lastSignal: last signal from executed functions.
 * @cmdNum: the executed command number.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: (0) always success, (1) otherwise.
*/
int _setenv(Commands *CMD, int *lastSignal, int cmdNum,
		char *programName, char *buffer)
{
	int index, setEnvLen;
	char *env, *setEnv, *enValue;

	(void) lastSignal, (void) cmdNum, (void) programName, (void) buffer;
	if (CMD->cmd[1] == NULL || CMD->cmd[2] == NULL)
		return (EXIT_SUCCESS);

	env = CMD->cmd[1];
	setEnv = _strdup(env);
	setEnv = _realloc(setEnv, _strlen(setEnv) + 1, _strlen(setEnv) + 2);
	setEnv[_strlen(env)] = '=';
	setEnv[_strlen(env) + 1] = '\0';

	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(setEnv, environ[index], _strlen(setEnv)) == 0)
			break;
	}

	enValue = CMD->cmd[2];
	setEnvLen = _strlen(setEnv);
	setEnv = _realloc(setEnv, setEnvLen + 1, setEnvLen + _strlen(enValue) + 1);

	setEnv = _strcat(setEnv, enValue);

	environ[index] = _strdup(setEnv);
	free(setEnv);
	return (EXIT_SUCCESS);
}
