#include "shell.h"

/**
 * main - function to implement the shell
 * CodesByAbdul
 * Return: 0.
 */
int main(void);

int main(void)
{
	char input[256];
	char **env_copy = environment();

	while (true)
	{
		prompt();
		user_input(input, sizeof(input));
		exec_input(input, env_copy);
	}

	free_env(env_copy);

	return (0);
}
