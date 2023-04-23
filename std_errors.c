#include "shell.h"

/**
* _eputs - prints a string to standard error
* @str: the string to be printed
*
* Return: Nothing
*/
void _eputs(char *str)
{
int i = 0;

if (!str)
return;

while (str[i] != '\0')
{
_eputchar(str[i]);
i++;
}
}

/**
* _eputchar - writes a character to standard error
* @c: The character to be written
*
* Return: On success, 1. On failure, -1 is returned
* and errno is set appropriately.
*/
int _eputchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}

if (c != BUF_FLUSH)
buf[i++] = c;

return (1);
}

/**
* _putfd - writes a character to a specified file
* descriptor
* @c: The character to be written
* @fd: The file descriptor to write to
*
* Return: On success, 1. On failure, -1 is returned
* and errno is set appropriately.
*/
int _putfd(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}

if (c != BUF_FLUSH)
buf[i++] = c;

return (1);
}

/**
* _putsfd - prints a string to a specified file
* descriptor
* @str: The string to be printed
* @fd: The file descriptor to write to
*
* Return: The number of characters written
*/
int _putsfd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);

while (*str)
{
i += _putfd(*str++, fd);
}

return (i);
}
