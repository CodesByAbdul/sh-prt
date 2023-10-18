#include "shell.h"

/**
 * pid - function to print process ID
 * CodesByAbdul
 * Return: 0.
 */

int pid(void)
{
	pid_t process_id;

	process_id = getpid();

	printf("Process ID: %u\n", process_id);
	return (0);
}
