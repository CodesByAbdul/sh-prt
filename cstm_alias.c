#include "shell.h"

/**
 * cstm_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int cstm_history(info_t *info)
{
	list_print(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = cstm_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_index(&(info->alias),
		getnode_index(info->alias, nodestarts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = cstm_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (addnode_end(&(info->alias), str, 0) == NULL);
}

/**
 * alias_print - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_print(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = cstm_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * cstm_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int cstm_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_print(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = cstm_strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			alias_print(nodestarts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
