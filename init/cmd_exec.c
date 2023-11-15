#include "shell.h"

/**
 * exec_input  - function to execute command
 * @args: command to be executed
 * CodesByAbdul
 * Return: 0
 */

void exec_input(char **args);

void exec_input(char **args)
{
	pid_t pid;

	if (args[0] == NULL)
	{
		/* empty command, do nothing */
		return;
	}

	if (strcmp(args[0], "exit") == 0)
	{
		/* handle exit command */

		/* cleanup */
		free(args);
		exit(EXIT_SUCCESS);
	}

	_environment(); /* call the function to setup environment */

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */

		/* Define the path to the command */
		char *command_path = "/bin/";
		char command[MAX_INPUT_SIZE];

		snprintf(command, sizeof(command), "%s%s", command_path, args[0]);


		/* Execute the command */
		if (execve(command, args, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, NULL, 0);
	}
}

















































































