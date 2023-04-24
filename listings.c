#include "shell.h"

/**
* add_node_to_start - Adds a node to the start of the list
* @head: Address of the pointer to the head node.
* @str: The string field of the node.
* @num: The node index used by history.
*
* Return: The size of the list.
*/
list_t *add_node_to_start(list_t **head, const char *str, int num)
{
list_t *new_head;

if (!head)
return (NULL);

new_head = malloc(sizeof(list_t));
if (!new_head)
return (NULL);

_memset((void *)new_head, 0, sizeof(list_t));
new_head->num = num;

if (str)
{
new_head->str = _strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}

new_head->next = *head;
*head = new_head;

return (new_head);
}

/**
* add_node_end - adds a node to the end of the list
* @head: address of pointer to head node
* @str: str field of node
* @num: node index used by history
*
* Return: address of new node
*/
list_t *add_node_end(list_t **head, const char *str, int num)
{
list_t *new_node, *node;

if (!head)
return (NULL);

new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);

_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = num;

if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}

new_node->next = NULL;

if (*head)
{
node = *head;
while (node->next)
node = node->next;
node->next = new_node;
}
else
{
*head = new_node;
}
return (new_node);
}

/**
* print_list_string - prints only the `str` element of a list_t linked list
* @head: pointer to the first node
*
* Return: size of the list
*/
size_t print_list_string(const list_t *head)
{
size_t size = 0;

while (head)
{
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
size++;
}
return (size);
}

/**
* delete_node - deletes node at given index
* @head: address of pointer to first node
* @index: index of node to delete
*
* Return: 1 on success, 0 on failure
*/
int delete_node(list_t **head, unsigned int index)
{
list_t *node, *prev;
unsigned int i = 0;

if (!head || !*head)
return (0);

if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}

node = *head;
while (node)
{
if (i == index)
{
prev->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev = node;
node = node->next;
}
return (0);
}

/**
* destroy_list - frees all nodes of a list
* @head: address of pointer to head node
*
* Return: void
*/
void destroy_list(list_t **head)
{
list_t *current, *next_node;

if (!head || !*head)
return;

current = *head;
while (current)
{
next_node = current->next;
free(current->str);
free(current);
current = next_node;
}

*head = NULL;
}
