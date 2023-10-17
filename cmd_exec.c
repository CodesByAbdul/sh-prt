#include "shell.h"

void exec_input(char *input)
{
	pid_t process_id;
	process_id = fork();
	int status;

	if (process_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (process_id == 0)
	{
		
		char command_path[200];	
		
		snprintf(command_path, sizeof(command_path), "bin/%s", input);
		
		char *argv[] = {input, NULL};
		
		execve(command_path, argv, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(&status);

}
