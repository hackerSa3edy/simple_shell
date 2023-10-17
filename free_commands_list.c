#include "main.h"

/**
 * free_commands - frees a Command type single list.
 *
 *  @list: Command type single list;
 *
 * Return: Nothing.
*/
void free_commands(Commands *list)
{
	Commands *tempList = list;
	int index;

	while (list != NULL)
	{
		tempList = list;
		if (list->op != NULL)
			free(list->op);

		for (index = 0; list->cmd[index] != NULL;)
			index++;

		free_2D(list->cmd, index);
		list = list->nextCmd;
		free(tempList);
	}
}
