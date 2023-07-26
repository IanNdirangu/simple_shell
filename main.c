#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info = INFO_INIT;
	int fd = STDERR_FILENO; /* Initialize to standard error*/

	/* Shift the file descriptor by 3*/
	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			/* Check the specific error condition and exit with the appropriate status code*/
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info.readfd = fd;
	}

	/* Initialize the environment list and read history*/
	populate_env_list(&info);
	read_history(&info);

	/* Call the shell function to start the main shell loop*/
	hsh(&info, av);

	return (EXIT_SUCCESS);
}

