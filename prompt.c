#include "shell.h"

/**
 * prompt - function to display prompt
 * CodesByAbdul
 * Return: 0.
 */

void prompt(void);

void prompt(void)
{
	if (isatty(0))
		_print("(CodesByAbdul Shell)\n$ ");
}
