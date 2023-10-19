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
	char *token, *cpy_input, **argv = NULL;
	int argc = 0, i, status;

	cpy_input = strdup(input);
	/* tokenization */
	token = strtok(cpy_input, " \t\n");
	while (token != NULL)
	{
		argv = realloc(argv, (argc + 1) * sizeof(char *));
		argv[argc] = strdup(token);
		argc++;
		token = strtok(NULL, " \t\n");
	}

	/*Null-terminate the arguments */
	argv = realloc(argv, (argc + 1) * sizeof(char *));
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

	free(cpy_input);
	for (i = 0; i < argc; i++)
	{
		free(argv[i]);
	}
	free(argv);
}
