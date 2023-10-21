#include "main.h"

/**
 * cd - change the current working directory.
 *
 * @CMD: Command type single list.
 * @lastSignal: last signal from executed functions.
 * @cmdNum: the executed command number.
 * @programName: the running executable name.
 * @buffer: the original buffer from getline function.
 *
 * Return: (0) always success, (EXIT_CODE) otherwise.
 */
int cd(Commands *CMD, int *lastSignal, int cmdNum,
		char *programName, char *buffer)
{
	char *dir = NULL, *cwd = NULL;
	char **env = NULL;
	int len, chdirStatus, retStatus;

	(void) lastSignal, (void) buffer;
	retStatus = EXIT_SUCCESS;
	for (len = 0; CMD->cmd[len];)
		len++;

	cwd = getcwd(cwd, 200);
	if (len == 1)
	{
		env = _getenv("HOME");
		if (env == NULL || *env == NULL)
		{
			free(cwd);
			if (*env == NULL)
				free(env);
			return (retStatus);
		}
		dir = *env;
	}
	else if (_strcmp(CMD->cmd[1], "-") == 0)
	{
		if (cd_preDir(&env, cwd, &dir))
			return (retStatus);
	}
	else
		dir = CMD->cmd[1];

	chdirStatus = chdir(dir);
	if (chdirStatus == 0)
		setenv("OLDPWD", cwd, 1);
	else
		retStatus = print_cdErr(programName, cmdNum, dir);
	if (env != NULL)
		free_2D(env, 1);
	free(cwd);
	return (retStatus);
}

/**
 * cd_prevDir - change the current working directory to
 *	the previous directory.
 *
 * @env: var to store the OLDPWD environment variable.
 * @cwd: the current working directory.
 * @dir: the directory to change to.
 *
 * Return: (0) always success, (1) otherwise.
 */
int cd_prevDir(char ***env, char *cwd, char **dir)
{
	*env = _getenv("OLDPWD");
	if (*env == NULL || **env == NULL)
	{
		write(STDOUT_FILENO, cwd, _strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		if (!(*env))
			free(*env);
		free(cwd);
		return (1);
	}
	*dir = **env;
	write(STDOUT_FILENO, *dir, _strlen(*dir));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/**
 * print_cdErr - prints cd errors.
 *
 * @programName: the executable program name.
 * @cmdNum: the executed command number.
 * @dir: the directory to change to.
 *
 * Return: (2) indicates cd error.
 */
int print_cdErr(char *programName, int cmdNum, char *dir)
{
	char *cmdNumStr = NULL;

	cmdNumStr = _btoi(cmdNum);
	write(STDERR_FILENO, programName, _strlen(programName));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmdNumStr, _strlen(cmdNumStr));
	write(STDERR_FILENO, ": cd: can't cd to ", _strlen(": cd: can't cd to "));
	write(STDERR_FILENO, dir, _strlen(dir));
	write(STDERR_FILENO, "\n", 1);
	free(cmdNumStr);

	return (2);
}
