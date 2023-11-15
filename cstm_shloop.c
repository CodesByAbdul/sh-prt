#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		info_clear(info);
		if (shell_interactive(info))
			_puts("(ShellByABDUL)$ ");
		cstm_putchar(BUF_FLUSH);
		r = read_input(info);
		if (r != -1)
		{
			info_set(info, av);
			builtin_ret = builtin_find(info);
			if (builtin_ret == -1)
				cmd_find(info);
		}
		else if (shell_interactive(info))
			_putchar('\n');
		info_free(info, 0);
	}
	write_hist(info);
	info_free(info, 1);
	if (!shell_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * builtin_find - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int builtin_find(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", cstm_exit},
		{"env", cstm_env},
		{"help", cstm_help},
		{"history", cstm_history},
		{"setenv", cstm_setenv},
		{"unsetenv", cstm_unsetenv},
		{"cd", cstm_cd},
		{"alias", cstm_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * cmd_find - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void cmd_find(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isdelim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = pathfinder(info, cstm_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		cmd_fork(info);
	}
	else
	{
		if ((shell_interactive(info) || cstm_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_execcmd(info, info->argv[0]))
			cmd_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			prerror(info, "not found\n");
		}
	}
}

/**
 * cmd_fork - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void cmd_fork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env(info)) == -1)
		{
			info_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				prerror(info, "Permission denied\n");
		}
	}
}
