#include "shell.h"

/**
 * cstm_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int cstm_exit(info_t *info)
{
	int checkexit;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		checkexit = _erratoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			prerror(info, "Illegal number: ");
			cstm_puts(info->argv[1]);
			cstm_putchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * cstm_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int cstm_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = cstm_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = cstm_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!cstm_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(cstm_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = cstm_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		prerror(info, "can't cd to ");
		cstm_puts(info->argv[1]), cstm_putchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", cstm_getenv(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * cstm_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int cstm_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
