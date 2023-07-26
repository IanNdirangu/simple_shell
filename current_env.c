#include "shell.h"

/**
 * display_environment - Displays the current environment variables.
 * @info: Pointer to the shell information struct.
 *
 * Return: Always 0.
 */
int display_environment(info_t *info)
{
	list_t *current_node = info->env;

	while (current_node)
	{
		_puts(current_node->str);
		_putchar('\n');
		current_node = current_node->next;
	}

	return (0);
}

/**
 * get_environment_variable - Gets the value of an environment variable.
 * @info: Pointer to the shell information struct.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *get_environment_variable(info_t *info, const char *name)
{
	list_t *current_node = info->env;
	size_t name_len = _strlen(name);

	while (current_node)
	{
		if (_strncmp(current_node->str, name, name_len) == 0)
		{
			char *value = current_node->str + name_len;
			if (*value == '=')
				return (value + 1);
		}
		current_node = current_node->next;
	}

	return (NULL);
}

/**
 * set_environment_variable - Initializes a new environment variable or modifies an existing one.
 * @info: Pointer to the shell information struct.
 * @name: The name of the environment variable.
 * @value: The value to be set for the environment variable.
 *
 * Return: 0 on success, 1 on error.
 */
int set_environment_variable(info_t *info, const char *name, const char *value)
{
	if (!name || !value)
		return (1);

	char *env_var = _strdupcat(name, "=", value);
	if (!env_var)
		return (1);

	_unset_environment_variable(info, name);
	return (add_node_end(&info->env, env_var, 0) ? 0 : 1);
}

/**
 * unset_environment_variable - Removes an environment variable from the list.
 * @info: Pointer to the shell information struct.
 * @name: The name of the environment variable to be removed.
 *
 * Return: 0 on success, 1 if the environment variable is not found.
 */
int unset_environment_variable(info_t *info, const char *name)
{
	list_t *current_node = info->env;
	list_t *prev_node = NULL;
	size_t name_len = _strlen(name);

	while (current_node)
	{
		if (_strncmp(current_node->str, name, name_len) == 0)
		{
			if (prev_node)
				prev_node->next = current_node->next;
			else
				info->env = current_node->next;
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
 * initialize_environment - Populates the environment linked list.
 * @info: Pointer to the shell information struct.
 *
 * Return: Always 0.
 */
int initialize_environment(info_t *info)
{
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&info->env, _strdup(environ[i]), 0);

	return (0);
}

