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

#define GOTO 2
extern char **environ;
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
	int (*func)(Commands *, int *, char *, char *);
} built_in_t;

Commands *parser(char *);
void *safeBuffer(char *);
char **tokenizedArray(char *, char *);
Commands *add_node_end(size_t, size_t, char *, char **, Commands **);
void SIGINT_handler(int);
char *_strdup(char *);
int _strlen(char *);
int _atoi(char *);
char *_btoi(int);
int num_of_digits(unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
char *_strcat(char *, char *);
int _strcmp(char *, char *);
int _strncmp(char *, char *, int);
char **_getenv(char *);
void free_2D(char **, int);
void executeCommand(Commands *, int *, int *, int, char *, char *, char *);
void execMe(Commands *, int *, int, char *, char *);
int (*built_in(char *))(Commands *, int *, char *, char *);
int absolutePath(char *);
char *commandExists(char *);
void free_commands(Commands *);
int doExec(int *, char *);
void execAbsolutePath(Commands *, int *, char *, char *);
void execCommandPath(Commands *, int *, char *, char *, char *);

/* Shell built-in functions*/
int ___exit(Commands *, int *, char *, char *);
int _env(Commands *, int *, char *, char *);

/* Logical operator handling functions */
int orOperator(Commands **, int *, char **, char **);
int andOperator(Commands **, int *, char **, char **);
int operatorsChain(Commands **, int *, char **, char **);

/* Error's print functions */
void print_notFoundErr(char *, int, char *);

/* Execute commands from a file function */
void execFile(char **, int *);

#endif /* MAIN_H */
