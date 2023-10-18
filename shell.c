#include "shell.h"

/**
 * main - function to implement the shell
 * CodesByAbdul
 * Return: 0.
 */

int main(void)
{
	char input[120];

	while (true)
	{
		prompt();
		user_input(input, sizeof(input));
		exec_input(input);
	}

	free(input);
	return (0);
}
