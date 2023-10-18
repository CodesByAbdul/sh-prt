#include "shell.h"
/**
 * user_input - function to read command from the terminal
 * @input: command from user
 * @len: length of command
 * CodesByAbdul
 * Return: 0.
 */

void user_input(char *input, size_t len)
{
	ssize_t nread;

	nread = getline(&input, &len, stdin);
	if (nread == -1)
	{
		if (feof(stdin))
		{
			printf("Exiting abshell ...\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	input[strcspn(input, "\n")] = '\0';

}
