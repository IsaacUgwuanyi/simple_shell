#include "shell.h"

/**
 * is_interactive - returns true if shell is in interactive mode
 * @shell_info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->read_fd <= 2);
}

/**
 * is_delimiter - checks if character is a delimiter
 * @c: the char to check
 * @delimiters: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_to_int - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int string_to_int(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
