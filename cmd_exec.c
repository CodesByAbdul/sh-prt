#include "shell.h"

/**
 * exec_input  - function to execute command
 * @input: command to be executed
 * @envp: environment variable
 * CodesByAbdul
 * Return: 0
 */
void exec_input(char *input, char **envp);

void exec_input(char *input, char **envp)
{
	pid_t process_id;
	char *token, *cpy_input;
	char **argv = NULL;
	int argc = 0;
	int i, status;

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
		if (strcmp(argv[0], "exit") == 0)
		{
			exit_shell(envp);
		}
		else if (strcmp(argv[0], "env") == 0)
		{
			print_environment(envp);
		}
		else if (strchr(argv[0], '/') == NULL)
		{
			char *path_env = getenv("PATH");

			if (path_env != NULL)
			{
				char *path = strtok(path_env, ":");
				int command_found = 0;

				while (path != NULL)
				{
					char command_path[256];

					snprintf(command_path, sizeof(command_path), "%s/%s", path, argv[0]);

					if (access(command_path, X_OK) == 0)
					{
						process_id = fork();

						if (process_id == -1)
						{
							perror("fork");
							exit(EXIT_FAILURE);
						}
						else if (process_id == 0)
						{
							execve(command_path, argv, envp);
							perror("execve");
							exit(EXIT_FAILURE);
						}
						else
						{
							wait(&status);
						}

						command_found = 1;
						break;
					}

					path = strtok(NULL, ":");
				}

				if (!command_found)
				{
					fprintf(stderr, "Command not found: %s\n", argv[0]);
				}
			else
			{
				fprintf(stderr, "PATH environment variable is not set\n");
			}
		}
		else
		{
			process_id = fork();

			if (process_id == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (process_id == 0)
			{
				execve(argv[0], argv, envp);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
			{
				wait(&status);
			}
		}
	}
	free(cpy_input);
	for (i = 0; i < argc; i++)
	{
		free(argv[i]);
	}
	free(argv);
	}
}
