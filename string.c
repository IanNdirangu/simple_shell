#include "shell.h"

/**
 * str_length - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int str_length(const char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (str[length] != '\0')
		length++;

	return (length);
}

/**
 * str_compare - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int str_compare(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);

		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * str_starts_with - checks if a string starts with a given prefix
 * @str: string to search
 * @prefix: the prefix to find
 *
 * Return: address of next character after prefix or NULL
 */
const char *str_starts_with(const char *str, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix != *str)
			return (NULL);

		prefix++;
		str++;
	}

	return (str);
}

/**
 * str_concatenate - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * @dest_size: the size of the destination buffer
 *
 * Return: pointer to destination buffer
 */
char *str_concatenate(char *dest, const char *src, int dest_size)
{
	int dest_len = str_length(dest);
	int src_len = str_length(src);
	int i;

	for (i = 0; i < dest_size - dest_len - 1 && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';
	return (dest);
}

