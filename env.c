#include "shell.h"

static char *environ[] = {
	"PATH=/bin:/usr/bin",
	"HOME=/home/user",
	NULL
};

/**
 * environment - function that gets the input environment
 * Return: copy Always
 */

char **environment(void)
{
	char **copy = (char **)malloc(sizeof(char *) * (env_size() + 1));
	int i;

	for (i = 0; environ[i] != NULL; i++)
		copy[i] = strdup(environ[i]);
	copy[i] = NULL;

	return (copy);
}

/**
 * env_size - size of the environment
 * Return: i Always
 */

int env_size(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
	}

	return (i);
}

/**
 * free_env - function to free allocated memory
 * @env: variable to free
 * Return: 0
 */

void free_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		free(env[i]);
	free(env);
}
