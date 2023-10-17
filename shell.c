#include "shell.h"

int main (void)
{
	char input[120];

	while(true)
	{
		prompt();
		user_input(input, sizeof(input));
		exec_input(input);
	}

	return (0);
}
