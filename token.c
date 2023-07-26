#include "shell.h"

/**
 * _strchr - locates the first occurrence of a character in a string.
 * @str: the string to search
 * @c: the character to locate
 *
 * Return: a pointer to the first occurrence of the character c in the string str,
 * or NULL if the character is not found.
 */
char *_strchr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (*str == c)
		return (str);
	return (NULL);
}

/**
 * word_count - counts the number of words in a string.
 * @str: the input string
 * @d: the delimiter string
 *
 * Return: the number of words in the string.
 */
int word_count(char *str, char *d)
{
	int count = 0;
	char *token;

	token = strtok(str, d);
	while (token)
	{
		count++;
		token = strtok(NULL, d);
	}
	return (count);
}

/**
 * strtow - splits a string into words. Repeat delimiters are ignored.
 * @str: the input string
 * @d: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (d == NULL || d[0] == '\0')
		d = " ";

	int numwords = word_count(str, d);
	if (numwords == 0)
		return (NULL);

	char **s = malloc((numwords + 1) * sizeof(char *));
	if (s == NULL)
		return (NULL);

	char *token;
	int i = 0;

	token = strtok(str, d);
	while (token)
	{
		s[i] = strdup(token);
		if (s[i] == NULL)
		{
			while (i > 0)
				free(s[--i]);
			free(s);
			return (NULL);
		}
		i++;
		token = strtok(NULL, d);
	}
	s[i] = NULL;
	return (s);
}

