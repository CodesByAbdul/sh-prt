#include "shell.h"
/**
 * custom_getline - custom getline function to read user input
 * Return: 0
 */

#define READ_SIZE 1024

char *custom_getline(void);

char *custom_getline(void)
{
	static char buffer[READ_SIZE];
	static size_t buffer_index;
	static size_t buffer_size;

	char *line = NULL;
	size_t line_size = 0;
	int character;

	while (1)
	{
		if (buffer_index >= buffer_size)
		{
			buffer_size = fread(buffer, 1, sizeof(buffer), stdin);
			buffer_index = 0;
			if (buffer_size == 0)
			{
				if (line_size == 0)
				{
					return (NULL); /* end of input */
				}
				break;/* End of line */
			}
		}

		character = buffer[buffer_index++];
		if (character == '\n' || character == EOF)
		{
			break;
		}

		line = (char *)realloc(line, line_size + 1);
		if (line == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}

		line[line_size++] = (char)character;
	}

	if (line_size > 0)
	{
		line = (char *)realloc(line, line_size + 1);
		if (line == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		line[line_size] = '\0';
		return (line);
	}
	else
	{
		return (NULL);  /* Empty line */
	}
	free(line);
}
