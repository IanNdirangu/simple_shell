#include "shell.h"

/**
 * write_string_to_fd - Writes a string to the given file descriptor
 * @str: The string to be written
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written.
 */
int write_string_to_fd(char *str, int fd)
{
	int i = 0;
	char buf[WRITE_BUF_SIZE];

	if (!str)
		return (0);

	while (*str)
	{
		buf[i++] = *str++;

		if (i >= WRITE_BUF_SIZE || *str == '\0')
		{
			write(fd, buf, i);
			i = 0;
		}
	}

	return (i);
}

/**
 * print_to_stderr - Writes a string to stderr
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void print_to_stderr(char *str)
{
	write_string_to_fd(str, STDERR_FILENO);
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	char buf[2] = {c, '\0'};
	write_string_to_fd(buf, STDERR_FILENO);
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	char buf[2] = {c, '\0'};
	write_string_to_fd(buf, fd);
	return (1);
}

/**
 * _putsfd - prints an input string to a given file descriptor
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
	return (write_string_to_fd(str, fd));
}

