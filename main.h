#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

/**
 * struct commands - single list of commands and logical operators.
 *
 * @cmd: command and its args in an array.
 * @op: logical operator which follows the command.
 * @nextCmd: pointer to the next node.
*/
typedef struct commands
{
	char **cmd;
	char *op;
	struct commands *nextCmd;
} Commands;

/**
 * struct built_in_s - single list of commands and logical operators.
 *
 * @cmd: command.
 * @func: function to execute the command.
*/
typedef struct built_in_s
{
	char *cmd;
	int (*func)(Commands *, char **, int *, char *);
} built_in_t;

Commands *parser(char *, ssize_t);
void *safeBuffer(char *, ssize_t);
char **tokenizedArray(char *, char *);
Commands *add_node_end(size_t, size_t, char *, char **, Commands **);
void SIGINT_handler(int);
char *_strdup(char *);
int _strlen(char *);
int _atoi(char *);
void *_realloc(void *, unsigned int, unsigned int);
char *_strcat(char *, char *);
int _strcmp(char *, char *);
int _strncmp(char *, char *, int);
char **_getenv(char *, char **);
void free_2D(char **, int);
int execMe(Commands *, char **, int *, char *);
int (*built_in(char *))(Commands *, char **, int *, char *);
int absolutePath(char *);
char *commandExists(char *, char **);
void free_commands(Commands *);
int doExec(int *, char *);
void execAbsolutePath(Commands *, int *, char **, char *);
void execCommandPath(Commands *, int *, char **, char *, char *);

/* Shell built-in functions*/

int ___exit(Commands *, char **, int *, char *);
int _env(Commands *, char **, int *, char *);

#endif /* MAIN_H */
