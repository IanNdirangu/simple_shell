#include "shell.h"

static char **environ_copy; /* Declare the static variable without initialization*/

/**
 * get_environ - Returns the string array copy of the environment.
 * @info: Structure containing potential arguments.
 * Return: The string array containing the environment variables.
 */
char **get_environ(info_t *info)
{
	if (!environ_copy || info->env_changed)
	{
		free_string_array(environ_copy);
		environ_copy = duplicate_string_array(info->env);
		info->env_changed = 0;
	}

	return (environ_copy);
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The string representing the environment variable to be removed.
 * Return: 1 on success (variable removed), 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	int changed = 0;
	char **environ_copy = get_environ(info);
	char **new_environ = NULL;
	int i, j;

	if (!environ_copy || !var)
		return (0);

	/* Count the number of variables that do not match the target variable*/
	for (i = 0; environ_copy[i]; i++)
	{
		if (!starts_with(environ_copy[i], var))
			changed++;
	}

	if (changed == i) /* No variable to remove*/
		return (0);

	new_environ = malloc((changed + 1) * sizeof(char *));
	if (!new_environ)
	{
		perror("_unsetenv");
		return (0);
	}

	/* Copy the environment variables to the new array, excluding the target variable*/
	for (i = 0, j = 0; environ_copy[i]; i++)
	{
		if (!starts_with(environ_copy[i], var))
		{
			new_environ[j] = strdup(environ_copy[i]);
			if (!new_environ[j])
			{
				perror("_unsetenv");
				free_string_array(new_environ);
				return (0);
			}
			j++;
		}
	}

	new_environ[changed] = NULL;

	/* Free the old environment and update the info struct*/
	free_string_array(info->env);
	info->env = new_environ;
	info->env_changed = 1;
	return (1);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The string representing the environment variable to be set/modified.
 * @value: The value to be set for the environment variable.
 * Return: 0 on success, 1 on error.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *new_var = NULL;
	char **environ_copy = get_environ(info);
	int changed = 0;

	if (!var || !value)
		return (1);

	/* Check if the variable already exists in the environment*/
	for (int i = 0; environ_copy[i]; i++)
	{
		if (starts_with(environ_copy[i], var))
		{
			new_var = malloc(strlen(var) + strlen(value) + 2);
			if (!new_var)
			{
				perror("_setenv");
				return (1);
			}
			sprintf(new_var, "%s=%s", var, value);
			free(environ_copy[i]);
			environ_copy[i] = new_var;
			changed = 1;
			break;
		}
	}

	if (!changed) /* If the variable is new, add it to the environment*/
	{
		int env_len = string_array_length(environ_copy);
		new_var = malloc(strlen(var) + strlen(value) + 2);
		if (!new_var)
		{
			perror("_setenv");
			return (1);
		}
		sprintf(new_var, "%s=%s", var, value);
		environ_copy = realloc(environ_copy, (env_len + 2) * sizeof(char *));
		if (!environ_copy)
		{
			perror("_setenv");
			free(new_var);
			return (1);
		}
		environ_copy[env_len] = new_var;
		environ_copy[env_len + 1] = NULL;
	}

	/* Free the old environment and update the info struct*/
	free_string_array(info->env);
	info->env = environ_copy;
	info->env_changed = 1;
	return (0);
}

