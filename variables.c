/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;
	int cmd_buf_type = CMD_CHAIN;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
	}
	else
	{
		return (0);
	}

	*p = j;
	info->cmd_buf_type = cmd_buf_type;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[i] = 0;
		j = len;
	}
	if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[i] = 0;
		j = len;
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;
	int replaced = 0;

	for (i = 0; i < 10 && info->argv[0]; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			break;
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			break;
		p = _strdup(p + 1);
		if (!p)
			break;
		info->argv[0] = p;
		replaced = 1;
	}
	return (replaced);
}
/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;
	int replaced = 0;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			replaced = 1;
			continue;
		}

	}
}
/**
 * replace_string - replaces string
 * @old: address of old string
 * @new_str: new string
 * Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new_str)
{
if (!new_str)
return (0);

char *temp = *old;
*old = new_str;
free(temp);

return (1);
}
