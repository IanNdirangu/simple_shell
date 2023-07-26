#include "shell.h"

/**
 * check_cmd_buffer_type - checks if the current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int check_cmd_buffer_type(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* Found end of this command */
	{
		buf[j] = 0; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = j;
	return (1);
}

/**
 * check_continue_chaining - checks if we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_continue_chaining(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	list_t *alias_node = node_starts_with(info->alias, info->argv[0], '=');
	if (!alias_node)
		return (0);

	char *alias_value = _strchr(alias_node->str, '=') + 1;
	replace_string(&(info->argv[0]), _strdup(alias_value));

	return (1);
}

/**
 * replace_vars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	for (int i = 0; info->argv[i]; i++)
	{
		char *arg = info->argv[i];
		if (arg[0] == '$')
		{
			if (!_strcmp(arg, "$?"))
				replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
			else if (!_strcmp(arg, "$$"))
				replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
			else
			{
				list_t *env_node = node_starts_with(info->env, &arg[1], '=');
				if (env_node)
				{
					char *env_value = _strchr(env_node->str, '=') + 1;
					replace_string(&(info->argv[i]), _strdup(env_value));
				}
				else
					replace_string(&(info->argv[i]), _strdup(""));
			}
		}
	}

	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

