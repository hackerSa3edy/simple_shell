#include "main.h"

/**
 * _unsetenv - unset environment variable.
 *
 * @CMD: the command that the user type.
 * @lastSignal: last signal from executed functions.
 * @cmdNum: the executed command number.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: (0) always success, (1) otherwise.
*/
int _unsetenv(Commands *CMD, int *lastSignal, int cmdNum,
		char *programName, char *buffer)
{
	char *env, *unsetEnv;
	int index, environLen, newEnvironLen = 0;

	(void) buffer;
	(void) programName;
	(void) cmdNum;
	(void) lastSignal;
	if (CMD->cmd[1] == NULL)
		return (EXIT_SUCCESS);

	for (environLen = 0; environ[environLen];)
		environLen++;

	env = CMD->cmd[1];
	unsetEnv = _strdup(env);
	unsetEnv = _realloc(unsetEnv, _strlen(unsetEnv) + 1, _strlen(unsetEnv) + 2);
	unsetEnv[_strlen(env)] = '=';
	unsetEnv[_strlen(env) + 1] = '\0';

	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(unsetEnv, environ[index], _strlen(unsetEnv)) != 0)
		{
			environ[newEnvironLen] = environ[index];
			newEnvironLen++;
		}
	}
	environ[newEnvironLen] = NULL;
	free(unsetEnv);
	return (EXIT_SUCCESS);
}
