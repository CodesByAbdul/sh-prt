#include "shell.h"

/**
 * print_environment - function to print environment
 * @envp: environment command
 * Return: 0
 */
void print_environment(char **env);

void print_environment(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
