#include "shell.h"

static char *environ[] = {
	"PATH=/bin:/usr/bin",
	"HOME=/home/user",
	NULL
};

/**
 * environment - function that gets the input environment
 * Return: copy of the environment
 */
char **environment(void);

char **environment(void)
{
	int size = env_size();
	char **copy = (char **)malloc(sizeof(char *) * (size + 1));
	int i;

	if (copy == NULL)
	{
		return (NULL);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		copy[i] = strdup(environ[i]);
		if (copy[i] == NULL)
		{
			free_env(copy);
			return (NULL);
		}
	}
	copy[size] = NULL;
	return (copy);
}


/**
 * env_size - size of the environment
 * Return: the size of the environment
 */
int env_size(void);

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
void free_env(char **env);

void free_env(char **env)
{
	int i;

	if (env == NULL)
	{
		return;
	}
	for (i = 0; env[i] != NULL; i++)
		free(env[i]);
	free(env);
}
