#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

void prompt(void);
void user_input(char *input, size_t len);
void exec_input(char *input, char **envp);
char **environment(void);
int env_size(void);
void free_env(char **env);
void exit_shell(char **env_copy);
void print_environment(char **env);
char *custom_getline(void);

#endif
