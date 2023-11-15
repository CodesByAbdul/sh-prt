#include "shell.h"

/**
 * main - function to implement the shell
 * CodesByAbdul
 * Return: 0.
 */
int main(void);

int main(void)
{
	char *input;
	char **args;

	while (1)
	{
		prompt();
		input = user_input();
		args = input_token(input);

		if (args[0] != NULL)
		{
			exec_input(args);
		}
		/* cleanup */
		free(input);
		free(args);
	}

	return (0);
}
