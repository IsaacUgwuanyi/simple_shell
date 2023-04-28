#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *info);
} builtin_table;


/* toem_shell_loop.c */
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* toem_parsing.c */
int check_executable(char *path);
char *copy_chars(const char *source, int start, int end);
char *findCmdPath(info_t *info, char *path, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* toem_std_errors.c */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_str.c */
int _str_len(char *str);
int _str_cmp(char *s1, char *s2);
char *starts_with_str(const char *haystack, const char *needle);
char *_str_concat(char *dest, char *src);

/* toem_str1.c */
char *_string_copy(char *dest, char *src);
char *_string_duplicate(const char *str);
void _write_string(char *str);
int _write_character(char c);

/* toem_str_exits.c */
char *_copyString(char *destination, const char *source, size_t maxChars);
char *_concatStrings(char *destination, const char *source, size_t maxChars);
char *_findChar(const char *string, char ch);

/* toem_str_tok.c */
char **strtow1(char *str, char *d);
char **strtow2(char *str, char d);

/* toem_mem_alloc.c */
char *memorySet(char *block, char byte, unsigned int size);
void freeStringArray(char **stringArray);
void *memoryRealloc(void *ptr, unsigned int oldSize, unsigned int newSize)

/* toem_shellmemory.c */
int free_ptr(void **ptr);

/* toem_custom_shell_functions.c */
iint is_interactive(info_t *shell_info);
int is_delimiter(char c, char *delimiters);
int is_alpha(int c);
int string_to_int(char *str);

/* toem_std_errors1.c */
int string_to_int(char *str);
void print_error_msg(info_t *info, char *err_msg);
int print_int(int n, int fd);
char *num_to_string(long int num, int base, int flags);
void remove_comments(char *buf);

/* toem_Inbuilts.c */
int exit_shell(command_info_t *command_info);
int change_directory(command_info_t *command_info);
int help_command(command_info_t *command_info);

/* toem_Inbuilts1.c */
int _myhistory(info_t *info);
int _myalias(info_t *info);

/*toem_gets.c */
ssize_t read_buffer(info_t *info, char *buffer, size_t *size);
int getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* toem_getsinfo.c */
void init_shell_info(shell_info_t *shell_info);
void set_shell_info(shell_info_t *shell_info, char **argv);
void free_shell_info(shell_info_t *shell_info, int all);

/* toem_environment.c */
char *get_env_var(info_t *info, const char *name);
int set_env_var(info_t *info);
int unset_env_var(info_t *info);
int unset_env_var(info_t *info);
int populate_env_list(info_t *info);

/* toem_gets1.c */
char **get_environment(info_t *info);
int _delete_env(info_t *info, char *var);
int _initialize_or_modify_env_var(info_t *info, char *var, char *value);

/* toem_getshistory.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_listings.c */
list_t *add_node_to_start(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_string(const list_t *head);
int delete_node(list_t **head, unsigned int index);
void destroy_list(list_t **head);

/* toem_listings1.c */
size_t list_count(const list_t *h);
char **list_to_str_array(list_t *head);
size_t print_list(const list_t *head);
list_t *find_node_with_prefix(list_t *head, char *prefix, char next_char);
ssize_t get_node_index(list_t *head, list_t *node);

/* toem_variables.c */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new_str);

#endif
