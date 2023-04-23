#include "shell.h"

/**
 * string_to_int - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int string_to_int(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_msg - prints an error message
 * @info: the parameter & return info struct
 * @err_msg: string containing specified error message
 * Return: void
 */
void print_error_msg(info_t *info, char *err_msg)
{
	_eputs(info->fname);
	_eputs(": ");
	print_int(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(err_msg);
}

/**
 * print_int - function prints a decimal (integer) number (base 10)
 * @n: the input integer
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_int(int n, int fd)
{
	int (*_putchar_func)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		_putchar_func = _eputchar;
	if (n < 0)
	{
		_abs_ = -n;
		_putchar_func('-');
		count++;
	}
	else
		_abs_ = n;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_putchar_func('0' + current / i);
			count++;
		}
		current %= i;
	}
	_putchar_func('0' + current);
	count++;

	return (count);
}

/**
 * num_to_string - function converts a number to string format
 * @num: number to be converted
 * @base: the base of the number
 * @flags: argument flags
 *
 * Return: string format of the number
 */
char *num_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: void
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i
}
