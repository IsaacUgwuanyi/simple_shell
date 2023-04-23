#include "shell.h"

/**
* get_environment - returns the string array copy of the environment variable
* @info: Structure containing arguments. Used to
* maintain constant function prototype.
*
* Return: Returns the environment variable as a string array copy.
*/
char **get_environment(info_t *info)
{
if (!info->environment || info->env_changed)
{
info->environment = list_to_strings(info->env);
info->env_changed = 0;
}

return (info->environment);
}

/**
* _delete_env - Removes an environment variable
* @info: Structure containing arguments. Used to
* maintain constant function prototype.
*
* Return: Returns 1 on successful deletion, 0 otherwise.
* @var: The environment variable to be deleted.
*/
int _delete_env(info_t *info, char *var)
{
list_t *node = info->env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}

/**
* _initialize_or_modify_env_var - Initialize a new
* environment variable, or modify an existing one
* @info: Structure containing arguments. Used to
* maintain constant function prototype.
* @var: The name of the environment variable.
* @value: The value of the environment variable.
*
* Return: Returns 0 on success, 1 on failure.
*/
int _initialize_or_modify_env_var(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = info->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}

