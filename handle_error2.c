#include "shell.h"

/**
 * parse_string_to_int - Parses a string and converts it to an integer.
 * @s: The string to be converted.
 *
 * Return: The integer value of the string, or -1 on error.
 */
int parse_string_to_int(char *s)
{
	int result = 0;

	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
		{
			int digit = *s - '0';

			/* Check for overflow*/
			if (result > (INT_MAX - digit) / 10)
				return (-1);

			result = result * 10 + digit;
		}
		else
			return (-1);

		s++;
	}

	return (result);
}

/**
 * print_error_message - Prints an error message to stderr.
 * @info: The pointer to the shell information struct.
 * @error_message: The string containing the specified error message.
 *
 * Return: Nothing.
 */
void print_error_message(info_t *info, char *error_message)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_message);
}

/**
 * print_decimal - Prints a decimal (integer) number to the given file descriptor.
 * @input: The input integer.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int input, int fd)
{
	int count = 0;
	char sign = (input < 0) ? '-' : '\0';
	unsigned int absolute_value = (input < 0) ? -input : input;

	if (fd == STDERR_FILENO)
		_putchar = _eputchar;

	if (input == 0)
	{
		_putchar('0');
		count++;
	}

	while (absolute_value)
	{
		int digit = absolute_value % 10;
		_putchar('0' + digit);
		count++;
		absolute_value /= 10;
	}

	if (sign)
	{
		_putchar(sign);
		count++;
	}

	_putchar = _putchar;
	return (count);
}

/**
 * convert_number_to_string - Converts a number to a string representation.
 * @num: The number to be converted.
 * @base: The base for the conversion (e.g., base 10 or base 16).
 *
 * Return: The string representation of the number.
 */
char *convert_number_to_string(long int num, int base)
{
	static char buffer[50];
	char *ptr = &buffer[49];
	unsigned long n = (num < 0) ? -num : num;

	if (num == 0)
	{
		*ptr = '0';
		ptr--;
	}

	while (n != 0)
	{
		*ptr = (n % base < 10) ? (n % base) + '0' : (n % base) + 'A' - 10;
		n /= base;
		ptr--;
	}

	if (num < 0)
	{
		*ptr = '-';
		ptr--;
	}

	return (ptr + 1);
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0' to remove comments.
 * @buf: The address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_comments(char *buf)
{
	while (*buf != '\0')
	{
		if (*buf == '#' && (buf == buf || *(buf - 1) == ' '))
		{
			*buf = '\0';
			break;
		}

		buf++;
	}
}

