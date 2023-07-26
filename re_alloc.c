#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_string_array - frees a string array (array of strings)
 * @str_array: the string array to be freed
 */
void free_string_array(char **str_array)
{
	if (!str_array)
		return;

	char **current_str = str_array;
	while (*current_str)
	{
		free(*current_str);
		current_str++;
	}

	free(str_array);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated memory block or NULL if allocation fails
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	char *new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	unsigned int copy_size = old_size < new_size ? old_size : new_size;
	_memset(new_ptr, 0, new_size);
	for (unsigned int i = 0; i < copy_size; i++)
		new_ptr[i] = ((char *)ptr)[i];

	free(ptr);
	return (new_ptr);
}

