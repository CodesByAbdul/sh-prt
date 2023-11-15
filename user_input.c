#include "shell.h"
/**
 * user_input - function to read command from the terminal
 * Return: 0.
 */
char *user_input(void);

char *user_input(void)
{
	char *input = NULL;
	size_t input_size = 0;

	if (getline(&input, &input_size, stdin) == -1)
	{
		perror("getline");
		free(input);
		exit(EXIT_FAILURE);
	}

    /* Remove the newline character */
	input[strcspn(input, "\n")] = '\0';

	return (input);

}
