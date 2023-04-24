#include "shell.h"

/**
* memorySet - fills a memory block with a given byte
* @block: pointer to the memory block
* @byte: byte to fill the memory block with
* @size: the size of the memory block
* Return: (block) a pointer to the memory block
*/
char *memorySet(char *block, char byte, unsigned int size)
{
unsigned int i;

for (i = 0; i < size; i++)
block[i] = byte;

return (block);
}

/**
* freeStringArray - frees a string array
* @stringArray: the string array to be freed
*/
void freeStringArray(char **stringArray)
{
char **ptr = stringArray;

if (!stringArray)
return;

while (*stringArray)
free(*stringArray++);

free(ptr);
}

/**
* memoryRealloc - reallocates a block of memory
* @ptr: pointer to previous malloc'ed block
* @oldSize: size in bytes of previous block
* @newSize: size in bytes of new block
*
* Return: pointer to the reallocated memory block
*/
void *memoryRealloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
char *newBlock;

if (!ptr)
return (malloc(newSize));

if (!newSize)
return (free(ptr), NULL);

if (newSize == oldSize)
return (ptr);

newBlock = malloc(newSize);
if (!newBlock)
return (NULL);

oldSize = oldSize < newSize ? oldSize : newSize;
while (oldSize--)
newBlock[oldSize] = ((char *)ptr)[oldSize];

free(ptr);
return (newBlock);
}

