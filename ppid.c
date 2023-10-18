#include "shell.h"

/**
 * ppid - function to print parent process ID
 * CodesByAbdul
 * Return: 0.
 */

int ppid(void)
{
	pid_t process_id;

	process_id = getppid();

	printf("Parent Process ID: %u\n", process_id);
	return (0);
}
