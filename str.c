#include "shell.h"

/**
* _str_len - returns the length of a string
* @str: the string whose length to check
*
* Return: integer length of string
*/
int _str_len(char *str)
{
int len = 0;

if (!str)
return (0);

while (*str++)
len++;
return (len);
}

/**
* _str_cmp - compares two strings lexicographically.
* @s1: the first string
* @s2: the second string
*
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int _str_cmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}

/**
* starts_with_str - checks if the string 'needle'
* starts with the string 'haystack'
* @haystack: string to search
* @needle: the substring to find
*
* Return: pointer to the next character of the
* 'haystack' if 'needle' is found or NULL if not
*/
char *starts_with_str(const char *haystack, const char *needle)
{
while (*needle)
{
if (*needle++ != *haystack++)
return (NULL);
}
return ((char *)haystack);
}

/**
* _str_concat - concatenates two strings
* @dest: the destination buffer
* @src: the source buffer
*
* Return: pointer to the destination buffer
*/
char *_str_concat(char *dest, char *src)
{
char *ret = dest;

while (*dest)
dest++;

while (*src)
*dest++ = *src++;

*dest = *src;

return (ret);
}

