#include "shell.h"

/**
* print_env - Prints the current environment variables.
* @info: A pointer to the info_t structure.
* Return: Always 0.
*/
int print_env(info_t *info)
{
print_list_strings(info->env);
return (0);
}

/**
* get_env_var - Gets the value of an environment variable.
* @info: A pointer to the info_t structure.
* @name: The name of the environment variable.
*
* Return: The value of the environment variable.
*/
char *get_env_var(info_t *info, const char *name)
{
list_t *node = info->env;
char *p;

while (node)
{
p = find_env_var(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
* set_env_var - Initializes a new environment variable
* or modifies an existing one.
* @info: A pointer to the info_t structure.
*
* Return: Always 0.
*/
int set_env_var(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguments.\n");
return (1);
}
if (update_env_var(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
* unset_env_var - Removes an environment variable.
* @info: A pointer to the info_t structure.
*
* Return: Always 0.
*/
int unset_env_var(info_t *info)
{
int i;

if (info->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
delete_env_var(info, info->argv[i]);

return (0);
}

/**
* populate_env_list - Populates the environs list
* @info: A pointer to the info_t structure.
*
* Return: Always 0.
*/
int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
