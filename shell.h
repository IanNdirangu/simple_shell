#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h> /* For size_t*/

#define CMD_BUFSIZE 64
#define WRITE_BUF_SIZE 1024

/* Structure to store shell information */
typedef struct shell_info
{
	int read_fd;			/* File descriptor for reading input */
	int status;				/* Exit status of the last command */
	int err_num;			/* Error number for last error */
	int argc;				/* Number of arguments in argv */
	char **argv;			/* Array of command-line arguments */
	char **env;				/* Array of environment variables */
	int env_changed;		/* Flag indicating if environment changed */
	char *fname;			/* Name of the executable file */
	int line_count;			/* Count of lines read from input */
	struct list_s *alias;	/* Linked list for storing aliases */
	struct list_s *history; /* Linked list for command history */
} info_t;

/* Singly linked list node structure */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/* Function prototypes */
int is_interactive_shell(info_t *shell_info);
int is_delimiter(char ch, const char *delimiters);
int is_alphabetic(char ch);
int string_to_integer(const char *str);
int custom_exit(info_t *info);
int custom_cd(info_t *info);
int custom_help(info_t *info);
int _is_number(const char *str);
char *_getcwd(void);
int display_history(info_t *info);
int unset_alias(info_t *info, char *alias);
int set_alias(info_t *info, char *alias);
int print_alias(list_t *node);
int manage_alias(info_t *info);
int display_environment(info_t *info);
char *get_environment_variable(info_t *info, const char *name);
int set_environment_variable(info_t *info, const char *name, const char *value);
int unset_environment_variable(info_t *info, const char *name);
int initialize_environment(info_t *info);
int write_string_to_fd(char *str, int fd);
void print_to_stderr(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int parse_string_to_int(char *s);
void print_error_message(info_t *info, char *error_message);
int print_decimal(int input, int fd);
char *convert_number_to_string(long int num, int base);
void remove_comments(char *buf);
char *read_input(info_t *info);
char **split_commands(info_t *info, char *input);
void remove_trailing_newline(char *str);
char *get_input(info_t *info);
void sigintHandler(int sig_num);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

/* Function prototypes for new functions */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
char **split_arguments(char *arg);
int count_arguments(char **argv);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

list_t *create_node(const char *str, int num);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

void safe_free(void **ptr);
int is_cmd(info_t *info, char *path);
char *find_path(info_t *info, char *pathstr, char *cmd);

/* Additional function prototypes */
char *_strncpy(char *dest, const char *src, size_t n);
char *_strncat(char *dest, const char *src, size_t n);
char *_strchr(const char *s, int c);

#endif /* SHELL_H */

