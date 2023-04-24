#include "shell.h"

/**
* list_count - counts the number of nodes in a linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t list_count(const list_t *h)
{
size_t i = 0;

while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
* list_to_str_array - converts a linked list to an array of strings
* @head: pointer to first node
*
* Return: array of strings
*/
char **list_to_str_array(list_t *head)
{
list_t *node = head;
size_t len = list_count(head), i, j;
char **str_array;
char *str;

if (!head || !len)
return (NULL);

str_array = malloc(sizeof(char *) * (len + 1));
if (!str_array)
return (NULL);

for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(str_array[j]);
free(str_array);
return (NULL);
}

str = _strcpy(str, node->str);
str_array[i] = str;
}
str_array[i] = NULL;
return (str_array);
}

/**
* print_list - prints all elements of a list_t linked list
* @head: pointer to first node
*
* Return: size of list
*/
size_t print_list(const list_t *head)
{
size_t count = 0;

while (head)
{
_puts(convert_number(head->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
count++;
}

return (count);
}

/**
* find_node_with_prefix - returns the node whose string starts with prefix
* @head: pointer to list head
* @prefix: string to match
* @next_char: the next character after prefix to match
*
* Return: pointer to the matched node, or NULL if not found
*/
list_t *find_node_with_prefix(list_t *head, char *prefix, char next_char)
{
while (head)
{
if (starts_with(head->str, prefix))
{
if (next_char == -1 || head->str[strlen(prefix)] == next_char)
return (head);
}
head = head->next;
}

return (NULL);
}

/**
* get_node_index - gets the index of a node
* @head: pointer to list head
* @node: pointer to the node
*
* Return: the index of node or -1 if node is not found
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t index = 0;

while (head)
{
if (head == node)
return (index);
head = head->next;
index++;
}

return (-1);
}

