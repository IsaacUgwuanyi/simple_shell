#include "shell.h"

/**
 * init_shell_info - initializes shell_info struct
 * @shell_info: struct address
 */
void init_shell_info(shell_info_t *shell_info)
{
	shell_info->args = NULL;
	shell_info->argv = NULL;
	shell_info->path = NULL;
	shell_info->arg_count = 0;
}

/**
 * set_shell_info - sets shell_info struct fields
 * @shell_info: struct address
 * @argv: argument vector
 */
void set_shell_info(shell_info_t *shell_info, char **argv)
{
	int i = 0;

	shell_info->fname = argv[0];
	if (shell_info->args)
	{
		shell_info->argv = strtow(shell_info->args, " \t");
		if (!shell_info->argv)
		{
			shell_info->argv = malloc(sizeof(char *) * 2);
			if (shell_info->argv)
			{
				shell_info->argv[0] = _strdup(shell_info->args);
				shell_info->argv[1] = NULL;
			}
		}
		for (i = 0; shell_info->argv && shell_info->argv[i]; i++)
			;
		shell_info->arg_count = i;

		replace_aliases(shell_info);
		replace_variables(shell_info);
	}
}

/**
 * free_shell_info - frees shell_info struct fields
 * @shell_info: struct address
 * @all: true if freeing all fields
 */
void free_shell_info(shell_info_t *shell_info, int all)
{
	ffree(shell_info->argv);
	shell_info->argv = NULL;
	shell_info->path = NULL;
	if (all)
	{
		if (!shell_info->command_buffer)
			free(shell_info->args);
		if (shell_info->env_vars)
			free_list(&(shell_info->env_vars));
		if (shell_info->history)
			free_list(&(shell_info->history));
		if (shell_info->aliases)
			free_list(&(shell_info->aliases));
		ffree(shell_info->environ);
			shell_info->environ = NULL;
		bfree((void **)shell_info->command_buffer);
		if (shell_info->readfd > 2)
			close(shell_info->readfd);
		_putchar(BUF_FLUSH);
	}
}
