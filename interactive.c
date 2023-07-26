#include "shell.h"

/**
 * is_interactive_shell - Checks if the shell is running in interactive mode
 * @shell_info: Pointer to the shell information struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive_shell(shell_info_t *shell_info)
{
	int is_interactive = 0;
	if (is_terminal_open(STDIN_FILENO) && shell_info->read_fd <= 2)
	{
		is_interactive = 1;
	}
	return (is_interactive);
}

/**
 * is_delimiter - Checks if a character is a delimiter
 * @ch: The character to check
 * @delimiters: The string containing delimiters
 *
 * Return: 1 if ch is a delimiter, 0 otherwise
 */
int is_delimiter(char ch, const char *delimiters)
{
	int is_delim = 0;
	while (*delimiters)
	{
		if (*delimiters == ch)
		{
			is_delim = 1;
			break;
		}
		delimiters++;
	}
	return (is_delim);
}

/**
 * is_alphabetic - Checks if a character is alphabetic (letter)
 * @ch: The character to check
 *
 * Return: 1 if ch is alphabetic, 0 otherwise
 */
int is_alphabetic(char ch)
{
	int is_alpha = 0;
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		is_alpha = 1;
	}
	return (is_alpha);
}
/**
 * string_to_integer - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: The converted integer value, or 0 if no numbers in the string
 */
int string_to_integer(const char *str)
{
	int i = 0, sign = 1, has_digit = 0;
	unsigned int result = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			has_digit = 1;
			result = result * 10 + (str[i] - '0');
		}
		else if (has_digit)
		{
			break;
		}
		i++;
	}
	return (result * sign);
}
