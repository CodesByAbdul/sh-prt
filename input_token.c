#include "shell.h"

/**
 * input_token - function to tokenize input
 * @input: user input to parse
 * Return: 0
 */

char **input_token(char *input)
{
	int i;
	char *token;
	char **args = malloc(MAX_ARGS * sizeof(char *));

	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	i = 0;
	token = strtok(input, " ");

	while (token != NULL)
	{
		args[i] = strdup(token);
		if (!args[i])
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, " ");
		i++;
	}

	args[i] = NULL;  /* Null-terminate the array */

	return (args);
}
