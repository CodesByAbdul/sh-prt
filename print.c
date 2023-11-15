#include "shell.h"

/**
 * _putchar - function to print character
 * @c: character to be printed
 * Return: 0
 */

int _putchar (char c)
{
	return (write(1, &c, 1));
}

/**
 * _print - function to print string
 * @str: string to be printed
 * Return: 0
 */

int _print(char *str)
{
	int i = 0, count = 0;

	while (str[i])
	{
		count += _putchar(str[i++]);
	}

	return (count);
}
