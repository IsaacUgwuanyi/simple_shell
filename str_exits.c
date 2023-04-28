#include "shell.h"

/**
 * _copyString - Copies a string
 * @destination: The destination string to copy to
 * @source: The source string
 * @maxChars: The maximum number of characters to be copied
 * Return: The pointer to the destination string
 */
char *_copyString(char *destination, const char *source, size_t maxChars)
{
	char *ptr = destination;
	size_t i = 0;

	while (*source != '\0' && i < maxChars)
	{
		*destination++ = *source++;
		i++;
	}
	while (i++ < maxChars)
	{
		*destination++ = '\0';
	}
	return (ptr);
}

/**
 * _concatStrings - Concatenates two strings
 * @destination: The first string
 * @source: The second string
 * @maxChars: The maximum number of bytes to be used
 * Return: The pointer to the concatenated string
 */
char *_concatStrings(char *destination, const char *source, size_t maxChars)
{
	char *ptr = destination;

	while (*destination != '\0')
	{
		destination++;
	}
	size_t i = 0;

	while (*source != '\0' && i < maxChars)
	{
		*destination++ = *source++;
		i++;
	}
	if (i == maxChars)
	{
		*destination = '\0';
	}
	return (ptr);
}

/**
 * _findChar - Locates a character in a string
 * @string: The string to search
 * @ch: The character to look for
 * Return: A pointer to the character found, or NULL if not found
 */
char *_findChar(const char *string, char ch)
{
	while (*string != '\0')
	{
		if (*string == ch)
		{
			return ((char *)string);
		}
		string++;
	}
	return (NULL);
}
