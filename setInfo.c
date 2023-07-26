#include "shell.h"

/**
 * clear_info - Initializes info_t struct fields to NULL or 0.
 * @info: Pointer to the info_t struct.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes info_t struct with argument vector.
 * @info: Pointer to the info_t struct.
 * @av: Argument vector (array of strings).
 */
void set_info(info_t *info, char **av)
{
	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_arguments(info->arg);
		info->argc = count_arguments(info->argv);

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees memory allocated for info_t struct fields.
 * @info: Pointer to the info_t struct.
 * @all: If true, free all fields, otherwise only argv.
 */
void free_info(info_t *info, int all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		free(info->arg);
		info->arg = NULL;
		free_list(&(info->env));
		free_list(&(info->history));
		free_list(&(info->alias));
		free_string_array(info->environ);
		info->environ = NULL;
		free(info->cmd_buf);
		info->cmd_buf = NULL;
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * split_arguments - Splits the argument string into an array of arguments.
 * @arg: The argument string to be split.
 * Return: An array of strings containing the individual arguments.
 */
char **split_arguments(char *arg)
{
	char **argv = NULL;
	int argc = 0;

	if (arg)
	{
		char *token, *delimiters = " \t\n";
		token = strtok(arg, delimiters);

		while (token)
		{
			argv = realloc(argv, (argc + 1) * sizeof(char *));
			if (!argv)
			{
				perror("split_arguments");
				break;
			}
			argv[argc++] = strdup(token);
			token = strtok(NULL, delimiters);
		}
	}

	if (argv)
		argv[argc] = NULL;

	return (argv);
}

/**
 * count_arguments - Counts the number of arguments in the argv array.
 * @argv: The array of strings containing the arguments.
 * Return: The number of arguments in argv.
 */
int count_arguments(char **argv)
{
	int count = 0;
	if (argv)
	{
		for (; argv[count]; count++)
			;
	}
	return (count);
}

