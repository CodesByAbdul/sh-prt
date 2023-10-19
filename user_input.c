#include "shell.h"
/**
 * user_input - function to read command from the terminal
 * @input: command from user
 * @len: length of command
 * CodesByAbdul
 * Return: 0.
 */
void user_input(char *input, size_t len);

void user_input(char *input, size_t len)
{
	ssize_t nread;
	char *cpy_input;

	nread = getline(&input, &len, stdin);
	if (nread == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	if (input[nread - 1] == '\n')
	{
		input[nread - 1] = '\0';
		nread--;
	}

	cpy_input = malloc(nread + 1);
	if (cpy_input == NULL)
	{
		perror("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	strcpy(cpy_input, input);

	free(cpy_input);
}
