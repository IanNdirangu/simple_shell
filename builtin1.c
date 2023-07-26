#include "shell.h"

/**
 * display_history - Displays the history list, one command per line,
 *                   preceded with line numbers, starting at 0.
 * @info: Pointer to the shell information struct.
 *
 * Return: Always 0.
 */
int display_history(info_t *info)
{
	int line_number = 0;
	list_t *current_node = info->history;

	while (current_node)
	{
		_printf("%d %s\n", line_number, current_node->str);
		line_number++;
		current_node = current_node->next;
	}

	return (0);
}

/**
 * unset_alias - Removes an alias from the list of aliases.
 * @info: Pointer to the shell information struct.
 * @alias: The alias to be removed.
 *
 * Return: 0 on success, 1 if the alias is not found.
 */
int unset_alias(info_t *info, char *alias)
{
	list_t *current_node = info->alias;
	list_t *prev_node = NULL;

	while (current_node)
	{
		if (_starts_with(current_node->str, alias))
		{
			if (prev_node)
				prev_node->next = current_node->next;
			else
				info->alias = current_node->next;
			free(current_node->str);
			free(current_node);
			return (0);
		}

		prev_node = current_node;
		current_node = current_node->next;
	}

	return (1);
}

/**
 * set_alias - Adds or modifies an alias in the list of aliases.
 * @info: Pointer to the shell information struct.
 * @alias: The alias to be added or modified.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *alias)
{
	char *alias_name = NULL;
	char *alias_value = NULL;
	list_t *current_node = info->alias;

	alias_name = _strtok(alias, "=");
	alias_value = _strtok(NULL, "=");

	if (!alias_name || !alias_value)
		return (1);

	while (current_node)
	{
		if (_starts_with(current_node->str, alias_name))
		{
			free(current_node->str);
			current_node->str = _strdup(alias);
			return (0);
		}
		current_node = current_node->next;
	}

	return (add_node_end(&info->alias, _strdup(alias), 0) ? 0 : 1);
}

/**
 * print_alias - Prints an alias in the format: "alias_name='alias_value'\n".
 * @node: The alias node to be printed.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *alias_name = _strdup(node->str);
	char *alias_value = _strchr(alias_name, '=');

	if (!alias_value)
	{
		free(alias_name);
		return (1);
	}

	*alias_value = '\0';
	alias_value++;
	_printf("%s='%s'\n", alias_name, alias_value);
	free(alias_name);

	return (0);
}

/**
 * manage_alias - Manages the aliases based on command-line arguments.
 * @info: Pointer to the shell information struct.
 *
 * Return: Always 0.
 */
int manage_alias(info_t *info)
{
	if (info->argc == 1) /* If no arguments provided, print all aliases.*/
	{
		list_t *current_node = info->alias;
		while (current_node)
		{
			print_alias(current_node);
			current_node = current_node->next;
		}
	}
	else /* Process the provided alias arguments.*/
	{
		for (int i = 1; info->argv[i]; i++)
		{
			if (_strchr(info->argv[i], '='))
				set_alias(info, info->argv[i]);
			else
			{
				list_t *alias_node = node_starts_with(info->alias, info->argv[i], '=');
				if (alias_node)
					print_alias(alias_node);
			}
		}
	}

	return (0);
}

