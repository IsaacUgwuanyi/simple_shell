#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @info: information struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->line_count_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->history_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: information struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *chain_buf; /* the ';' command chain buffer */
	static size_t chain_buf_pos, cmd_pos, buf_len;
	ssize_t read_len = 0;
	char **cmd_buf = &(info->arg), *cmd_pos_ptr;

	_putchar(BUF_FLUSH);
	read_len = input_buffer(info, &chain_buf, &buf_len);
	if (read_len == -1) /* EOF */
		return (-1);

	if (buf_len) /* we have commands left in the chain buffer */
	{
		cmd_pos = chain_buf_pos;
		cmd_pos_ptr = chain_buf + chain_buf_pos; /* get pointer for return */

		check_chain(info, chain_buf, &cmd_pos, chain_buf_pos, buf_len);
		while (cmd_pos < buf_len) /* iterate to semicolon or end */
		{
			if (is_chain(info, chain_buf, &cmd_pos))
				break;
			cmd_pos++;
		}

		chain_buf_pos = cmd_pos + 1; /* increment past nulled ';'' */
		if (chain_buf_pos >= buf_len) /* reached end of buffer? */
		{
			chain_buf_pos = buf_len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*cmd_buf = cmd_pos_ptr; /* pass back pointer to current command position */
		return (_strlen(cmd_pos_ptr)); /* return length of current command */
	}

	*cmd_buf = chain_buf;
	return (read_len); /* return lengh of buffer from input_buffer() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @size: size
 *
 * Return: result
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *size)
{
	ssize_t result = 0;

	if (*size)
		return (0);
	result = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (result >= 0)
		*size = result;
	return (result);
}

/**
 * getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t position, length_buffer;
	size_t k;
	ssize_t result = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;
	if (position == length_buffer)
		position = length_buffer = 0;

	result = read_buffer(info, buffer, &length_buffer);
	if (result == -1 || (result == 0 && length_buffer == 0))
		return (-1);

	c = strchr(buffer + position, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : length_buffer;
	new_p = realloc(p, size, size ? size + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (size)
		strncat(new_p, buffer + position, k - position);
	else
		strncpy(new_p, buffer + position, k - position + 1);

	size += k - position;
	position = k;
	p = new_p;

	if (length)
		*length = size;
	*ptr = p;
	return (size);
}

/**
 * sigintHandler - signal handler for signINT that print
 * a prompt
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

