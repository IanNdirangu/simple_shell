#include "shell.h"

/**
 * str_copy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *str_copy(char *dest, const char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * str_duplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *str_duplicate(const char *str)
{
	if (str == NULL)
		return (NULL);

	int length = str_length(str);
	char *ret = malloc(sizeof(char) * (length + 1));

	if (!ret)
		return (NULL);

	for (int i = 0; i <= length; i++)
		ret[i] = str[i];

	return (ret);
}

/**
 * str_print - prints a string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void str_print(const char *str)
{
	if (!str)
		return;

	int i = 0;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * char_print - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int char_print(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

