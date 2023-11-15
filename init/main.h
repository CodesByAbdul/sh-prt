#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 1024

/* function prototypes */
int _putchar (char c);
int _print(char *str);
void prompt(void);
char *user_input(void);
char **input_token(char *input);
void _environment();
void exec_input(char **args);

#endif /* SHELL_H */
