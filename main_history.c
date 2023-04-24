#include "shell.h"

/**
 * main - entry point for shell program with command history
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	ShellInfo shell_info = SHELL_INFO_INIT;
	int fd = STDERR_FILENO;

	/* Check if a history file was specified as an argument */
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shell_info.readfd = fd;
	}

	populate_env_list(&shell_info);
	read_history(&shell_info);
	hsh(&shell_info, argv);

	return (EXIT_SUCCESS);
}
