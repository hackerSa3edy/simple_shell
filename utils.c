#include "main.h"

/**
 * SIGINT_handler - handles CTRL + C signal.
 *
 * @signal: signal to be handled.
 *
 * Return: Nothing.
*/
void SIGINT_handler(int signal)
{
		(void) signal;
		write(STDOUT_FILENO, "\n($) ", 5);
}

/**
 * add_node_end - adds a new node at the end of a Commands list.
 *
 * @prevIndex: the starting index.
 * @lastIndex: the end index.
 * @logicalOp: logical operator to be add to the node.
 * @tokens: array of commands to extract each command from it.
 * @head: the head Commands node.
 *
 * Return: the address of the new element, or NULL if it failed.
 */
Commands *add_node_end(size_t prevIndex, size_t lastIndex,
		char *logicalOp, char **tokens, Commands **head)
{
	Commands *new = malloc(sizeof(Commands));
	Commands *traverse = *head;
	size_t index;

	if (new == NULL)
		return (NULL);

	new->op = _strdup(logicalOp);

	new->cmd = malloc((lastIndex - prevIndex + 1) * sizeof(char *));
	if (new->cmd == NULL)
	{
		free(new->op);
		free(new);
		return (NULL);
	}
	new->nextCmd = NULL;
	for (index = 0; prevIndex < lastIndex; prevIndex++)
	{
		(new->cmd)[index] = _strdup(tokens[prevIndex]);
		if ((new->cmd)[index] == NULL)
		{
			free(new->op);
			free_2D(new->cmd, prevIndex);
			return (NULL);
		}
		index++;
	}
	(new->cmd)[index] = NULL;
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}

	while (traverse->nextCmd != NULL)
		traverse = traverse->nextCmd;

	traverse->nextCmd = new;
	return (new);
}

/**
 * free_2D - frees a 2 dimensional array previously created.
 *
 * @grid: 2 dimensional array.
 * @height: height of the array.
 *
 * Return: Nothing.
 */
void free_2D(char **grid, int height)
{
	int index;

	for (index = 0; index < height; index++)
	{
		free(grid[index]);
	}
	free(grid);
}

/**
 * absolutePath - checks if the command is absolute path to the binary or not.
 *
 * @cmd: command.
 *
 * Return: (1) absolute path, (0) otherwise.
*/
int absolutePath(char *cmd)
{
	int absPath = 0;

	if (cmd[0] == '.' && cmd[1] == '/')
		absPath = 1;
	else if (cmd[0] == '/')
		absPath = 1;
	else if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		absPath = 1;

	return (absPath);
}

/**
 * _getenv - gets the environment value for an env variable.
 *
 * @env: the environment variable.
 *
 * Return: array of env values for the env variable.
*/
char **_getenv(char *env)
{
	int index, len;
	char **PATH, **tempPATH;
	char **envs = environ;

	for (index = 0; envs[index] != NULL; index++)
	{
		if (_strncmp(envs[index], env, _strlen(env)) == 0)
		{
			PATH = tokenizedArray(envs[index], "=");
			break;
		}
	}
	for (len = 0; PATH[len] != NULL; len++)
		len++;

	tempPATH = PATH;
	PATH = tokenizedArray(PATH[1], ":");
	free_2D(tempPATH, len);

	return (PATH);
}
