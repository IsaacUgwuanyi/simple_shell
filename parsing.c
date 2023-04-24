#include "shell.h"

/**
* check_executable - checks if a file is an executable command
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int check_executable(char *path)
{
struct stat file_stat;

if (!path || stat(path, &file_stat))
return (0);

if (file_stat.st_mode & S_IFREG)
return (1);

return (0);
}

/**
* copy_chars - copies characters from a string
* @source: the source string
* @start: starting index
* @end: ending index
*
* Return: pointer to new buffer
*/
char *copy_chars(const char *source, int start, int end)
{
static char buffer[1024];
int i, j = 0;

for (i = start; i < end && j < 1023; i++, j++)
buffer[j] = source[i];

buffer[j] = '\0';

return (buffer);
}

/**
* findCmdPath - finds the path of the given command in
* the PATH environment variable
* @info: the info struct containing shell information
* @path: the PATH environment variable
* @cmd: the command to find
*
* Return: the full path of the command if found, or NULL
*/
char *findCmdPath(info_t *info, char *path, char *cmd)
{
int i = 0, curr_pos = 0;
char *pathCopy;

if (!path)
return (NULL);

if ((_strlen(cmd) > 2) && startsWith(cmd, "./"))
{
if (isCmd(info, cmd))
return (cmd);
}

while (1)
{
if (!path[i] || path[i] == ':')
{
pathCopy = duplicateChars(path, curr_pos, i);
if (!*pathCopy)
stringConcat(pathCopy, cmd);
else
{
stringConcat(pathCopy, "/");
stringConcat(pathCopy, cmd);
}

if (isCmd(info, pathCopy))
return (pathCopy);

if (!path[i])
break;

curr_pos = i;
}

i++;
}

return (NULL);
}

