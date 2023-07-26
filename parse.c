#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info; /* Unused parameter*/
	if (!path || stat(path, &st) != 0)
		return (0);

	return (S_ISREG(st.st_mode));
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	char *path = NULL;
	char *delimiter = ":";

	if (!pathstr || !cmd)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (_strdup(cmd));
	}

	while ((path = _strtok(pathstr, delimiter)) != NULL)
	{
		int path_len = _strlen(path);
		int cmd_len = _strlen(cmd);
		char *full_path = NULL;

		if (path[path_len - 1] != '/')
			full_path = _strcat(_strcat(_strdup(path), "/"), cmd);
		else
			full_path = _strcat(_strdup(path), cmd);

		if (is_cmd(info, full_path))
		{
			free(path);
			return (full_path);
		}

		free(full_path);
		pathstr = NULL; /* To continue with the same buffer in strtok_r*/
	}

	return (NULL);
}

