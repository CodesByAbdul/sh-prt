#include "shell.h"

/**
 * exit_shell - function to exit shell when user input exit
 * @env_copy: variable for the environment
 * Return: 0
 */

void exit_shell(char **env_copy)
{
	free_env(env_copy);

	exit(EXIT_SUCCESS);
}
