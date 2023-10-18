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
	char *token;
	char *argv[265]; /* Array to hold arguments */
	int argc = 0;
	/* char command_path[200]; */
	/* char *argv[2]; */
	int status;

	/* argv[0] = input; */
	/* argv[1] = NULL; */

	token = strtok(input, " \t\n");
	while (token != NULL)
	{
		argv[argc++] = token;
		token = strtok(NULL, " \t\n");
	}
	/*Null-terminate the arguments */
	argv[argc] = NULL;

	if (argc > 0)
	{
		process_id = fork();

		if (process_id == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (process_id == 0)
		{
			if (strchr(argv[0], '/') == NULL)
			{
		/**
		 * strncpy(command_path, input, sizeof(command_path));
		 * else
		 *	snprintf(command_path, sizeof(command_path), "/bin/%s", input);

		 *	if (execve(command_path, argv, envp) == -1)
		 *	{
		 *	perror("execve");
		 *	exit(EXIT_FAILURE);
		 *	}
		 */
				char command_path[256];

				snprintf(command_path, sizeof(command_path), "/bin/%s", argv[0]);
				execve(command_path, argv, envp);
			}
			else
			{
				execve(argv[0], argv, envp);
			}
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}
}
