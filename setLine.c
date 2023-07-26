#include "shell.h"

static char *input; /* Declare the static variable without initialization*/

/**
 * read_input - Read the next line of input from STDIN.
 * @info: Parameter struct containing potential arguments.
 * Return: The input line as a string or NULL on error or EOF.
 */
char *read_input(info_t *info)
{
	size_t bufsize = 0;
	char *input = NULL;
	ssize_t r;

	_puts("$ "); /* Print the shell prompt*/

	r = getline(&input, &bufsize, stdin); /* Read input from stdin*/
	if (r == -1)						  /* If there was an error or EOF*/
	{
		if (feof(stdin))
			_puts("\n"); /* Print a new line when reaching EOF*/
		else
			perror("read_input"); /* Print error message*/
		free(input);			  /* Free the allocated memory*/
		input = NULL;
	}

	return (input);
}

/**
 * split_commands - Split the input line into separate commands if there are semicolons.
 * @info: Parameter struct containing potential arguments.
 * @input: The input line to be split.
 * Return: An array of strings, each representing a separate command.
 */
char **split_commands(info_t *info, char *input)
{
	int bufsize = CMD_BUFSIZE;
	int position = 0;
	char **commands = malloc(bufsize * sizeof(char *));
	char *command;

	if (!commands)
	{
		perror("split_commands");
		exit(EXIT_FAILURE);
	}

	command = strtok(input, ";");
	while (command)
	{
		commands[position] = command;
		position++;

		if (position >= bufsize)
		{
			bufsize += CMD_BUFSIZE;
			commands = realloc(commands, bufsize * sizeof(char *));
			if (!commands)
			{
				perror("split_commands");
				exit(EXIT_FAILURE);
			}
		}

		command = strtok(NULL, ";");
	}
	commands[position] = NULL;

	return (commands);
}

/**
 * remove_trailing_newline - Remove the trailing newline character from a string.
 * @str: The string to be modified.
 * Return: Nothing.
 */
void remove_trailing_newline(char *str)
{
	int len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

/**
 * get_input - Get the next command from the input buffer.
 * @info: Parameter struct containing potential arguments.
 * Return: The next command as a string or NULL on error or EOF.
 */
char *get_input(info_t *info)
{
	char *command;

	if (input)
	{
		command = strtok(NULL, ";");
		if (command)
		{
			remove_trailing_newline(command);
			return (command);
		}
		free(input);
		input = NULL;
	}

	input = read_input(info);
	if (!input)
		return (NULL);

	remove_trailing_newline(input);
	return (strtok(input, ";"));
}

/**
 * sigintHandler - Blocks Ctrl+C signal handling.
 * @sig_num: The signal number.
 * Return: Void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n$ "); /* Print the shell prompt after handling SIGINT*/
}

