#include "main.h"

/**
 * parser - make a Commands single list of commands and its logical operators.
 *
 * @buffer: buffer to be parsed.
 * @bufferLen: buffer length.
 *
 * Return: pointer to the Commands single list.
 */
Commands *parser(char *buffer, ssize_t bufferLen)
{
	Commands *commands = NULL;
	size_t index, prevIndex = 0, foundOp = 0, firstCMD = 1;
	char **tokens = NULL;
	char *safe_buffer = NULL;

	safe_buffer = safeBuffer(buffer, bufferLen);
	tokens = tokenizedArray(safe_buffer, " ");
	free(safe_buffer);

	for (index = 0; tokens[index] != NULL; index++)
	{
		if (_strcmp(tokens[index], "||") == 0 && firstCMD != 1)
			foundOp = 1;
		else if (_strcmp(tokens[index], "&&") == 0 && firstCMD != 1)
			foundOp = 1;
		else if (_strcmp(tokens[index], ";") == 0 && firstCMD != 1)
			foundOp = 1;

		if (foundOp)
		{
			add_node_end(prevIndex, index, tokens[index], tokens, &commands);
			prevIndex = index + 1;
			foundOp = 0;
		}
		if (tokens[index + 1] == NULL)
			add_node_end(prevIndex, index + 1, NULL, tokens, &commands);
		firstCMD = 0;
	}

	free_2D(tokens, index);
	return (commands);
}

/**
 * safeBuffer - delete the last character '\n'.
 *
 * @buffer: buffer to processed.
 * @bufferLen: buffer length.
 *
 * Return: pointer to the safe buffer.
 */
void *safeBuffer(char *buffer, ssize_t bufferLen)
{
	char *safe_buffer = malloc(bufferLen);
	int index;

	for (index = 0; buffer[index + 1]; index++)
		safe_buffer[index] = buffer[index];

	safe_buffer[index] = '\0';
	return (safe_buffer);
}

/**
 * tokenizedArray - make each command and arg in
 *	the buffer into array.
 *
 * @safeBuffer: the buffer to be processed.
 * @delim: delimiter.
 *
 * Return: array of tokenized commands.
 */
char **tokenizedArray(char *safeBuffer, char *delim)
{
	char *tempSafeBuffer = NULL, *token = NULL;
	char **tokenized_array = NULL;
	size_t arrLen = 0;

	tempSafeBuffer = _strdup(safeBuffer);
	token = strtok(tempSafeBuffer, delim);
	while (token != NULL)
	{
		arrLen++;
		token = strtok(NULL, delim);
	}

	free(tempSafeBuffer);
	tempSafeBuffer = _strdup(safeBuffer);
	tokenized_array = malloc((arrLen + 1) * sizeof(char *));
	token = strtok(tempSafeBuffer, delim);
	arrLen = 0;

	while (token != NULL)
	{
		tokenized_array[arrLen] = _strdup(token);
		arrLen++;
		token = strtok(NULL, delim);
	}
	tokenized_array[arrLen] = NULL;
	free(tempSafeBuffer);
	return (tokenized_array);
}
