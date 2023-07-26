#include "shell.h"

/**
 * custom_exit - Exits the shell with a given exit status.
 * @info: Pointer to the shell information struct.
 *
 * Return: -1 if there is an error, 0 if successful.
 */
int custom_exit(info_t *info)
{
	if (!info->argv[1]) /*No argument provided, exit with success status*/
		return (0);

	int exit_code = 0;

	if (_is_number(info->argv[1])) /* Check if the argument is a valid number*/
		exit_code = _atoi(info->argv[1]);
	else
	{
		info->status = 2;
		print_error(info, "Illegal number: ");
		_eputs(info->argv[1]);
		_eputchar('\n');
		return (-1);
	}

	info->err_num = exit_code;
	return (-2);
}

/**
 * custom_cd - Changes the current directory of the process.
 * @info: Pointer to the shell information struct.
 *
 * Return: 0 if successful, -1 if there's an error.
 */
int custom_cd(info_t *info)
{
	char *target_dir = NULL;

	if (!info->argv[1]) /* No arguments provided, change to HOME directory*/
		target_dir = _get_environment_variable(info, "HOME");
	else if (_strcmp(info->argv[1], "-") == 0) /* Change to previous directory*/
	{
		target_dir = _get_environment_variable(info, "OLDPWD");
		if (!target_dir)
		{
			_puts("No previous directory found.\n");
			return (-1);
		}
		_puts(target_dir);
		_putchar('\n');
	}
	else /* Change to the specified directory*/
		target_dir = info->argv[1];

	if (!target_dir)
	{
		print_error(info, "No such directory: ");
		_eputs(info->argv[1]);
		_eputchar('\n');
		return (-1);
	}

	int chdir_result = chdir(target_dir);

	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(target_dir);
		_eputchar('\n');
		return (-1);
	}

	_set_environment_variable(info, "OLDPWD", _get_environment_variable(info, "PWD"));
	_set_environment_variable(info, "PWD", _getcwd());

	return (0);
}

/**
 * custom_help - Displays help information for shell commands.
 * @info: Pointer to the shell information struct.
 *
 * Return: Always 0.
 */
int custom_help(info_t *info)
{
	(void)info; /* Suppress unused parameter warning*/

	_puts("Help information is not yet implemented.\n");

	return (0);
}

/**
 * _is_number - Checks if a string is a valid integer number.
 * @str: The string to check.
 *
 * Return: 1 if the string is a valid number, 0 otherwise.
 */
int _is_number(const char *str)
{
	int i = 0;

	if (str[i] == '-')
		i++;

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}

	return (1);
}

/**
 * _getcwd - Gets the current working directory.
 *
 * Return: A pointer to the current working directory, NULL on failure.
 */
char *_getcwd(void)
{
	static char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (cwd);
	else
		return (NULL);
}
