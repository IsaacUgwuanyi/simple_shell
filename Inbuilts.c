#include "shell.h"

/**
 * exit_shell - exits the shell
 * @command_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if command_info->argv[0] != "exit"
 */
int exit_shell(command_info_t *command_info)
{
	int exit_code;

	if (command_info->argv[1]) /* If there is an exit argument */
	{
		exit_code = err_atoi(command_info->argv[1]);
		if (exit_code == -1)
		{
			command_info->status = 2;
			print_error(command_info, "Illegal number: ");
			_eputs(command_info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		command_info->err_num = err_atoi(command_info->argv[1]);
		return (-2);
	}
	command_info->err_num = -1;
	return (-2);
}

/**
 * change_directory - changes the current directory of the process
 * @command_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int change_directory(command_info_t *command_info)
{
	char *current_dir, *dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!command_info->argv[1])
	{
		dir = _getenv(command_info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(command_info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(command_info->argv[1], "-") == 0)
	{
		if (!_getenv(command_info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(command_info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(command_info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(command_info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(command_info, "can't cd to ");
		_eputs(command_info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(command_info, "OLDPWD", _getenv(command_info, "PWD="));
		_setenv(command_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_command - displays help information
 * @command_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int help_command(command_info_t *command_info)
{
	char **arg_array;

	arg_array = command_info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
