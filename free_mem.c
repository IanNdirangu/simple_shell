#include "shell.h"

/**
 * safe_free - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Description: This function safely frees the memory pointed by 'ptr'
 *              and sets the pointer to NULL to avoid a dangling pointer.
 *
 * Return: None
 */
void safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

