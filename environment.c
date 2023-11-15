#include "shell.h"

/**
 * _environment - function for environment variables
 */
void _environment(void)
{
	char *env[] = {"PATH=/bin:/usr/bin", NULL};

	if (execve(command, args, env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
