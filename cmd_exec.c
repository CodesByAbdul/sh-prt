#include "shell.h"

/**
 * exec_input  - function to execute command
 * @input: command to be executed
 * @envp: environment variable
 * CodesByAbdul
 * Return: 0
 */

void exec_input(char *input, char **envp)
{
	pid_t process_id;
	char command_path[200];
	char *argv[2];
	int status;

	argv[0] = input;
	argv[1] = NULL;

	process_id = fork();

	if (process_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (process_id == 0)
	{
		if (input[0] == '/')
			strncpy(command_path, input, sizeof(command_path));
		else
			snprintf(command_path, sizeof(command_path), "/bin/%s", input);

		if (execve(command_path, argv, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
