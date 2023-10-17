#include "shell.h"

int main (void)
{
	char input[120];
	size_t len = 0;

	while(true)
	{
		prompt();
		user_input(input, sizeof(len));
	}

	free(input);
	return (0);
}
