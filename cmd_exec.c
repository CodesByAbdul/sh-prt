#include "shell.h"

/**
 * exec_input  - function to execute command
 * @input: command to be executed
 * CodesByAbdul
 * Return: 0
 */
extern char **environ;

void exec_input(char *input)
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
		snprintf(command_path, sizeof(command_path), "/bin/%s", input);

		execve(command_path, argv, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}
