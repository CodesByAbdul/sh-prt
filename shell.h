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
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* cstm_shellloop.c */
int hsh(info_t *, char **);
int builtin_find(info_t *);
void cmd_find(info_t *);
void cmd_fork(info_t *);

/* cstmm_parser.c */
int is_execcmd(info_t *, char *);
char *char_dup(char *, int, int);
char *pathfinder(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* cstm_prints.c */
void cstm_puts(char *);
int cstm_putchar(char);
int cstm_putfd(char c, int fd);
int cstm_putsfd(char *str, int fd);

/* cstm_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* cstm_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* cstm_str.c */
char *cstm_strcpy(char *, char *, int);
char *cstm_strcat(char *, char *, int);
char *cstm_strchr(char *, char);

/* cstm_tokenizer.c */
char **strsplit(char *, char *);
char **strsplit2(char *, char);

/* cstm_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* cstm_memory.c */
int memfree(void **);

/* cstm_atoi.c */
int shell_interactive(info_t *);
int isdelim(char, char *);
int _is_alpha(int);
int _atoi(char *);

/* printerror.c */
int _erratoi(char *);
void prerror(info_t *, char *);
int printdec(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* cstm_builtin.c */
int cstm_exit(info_t *);
int cstm_cd(info_t *);
int cstm_help(info_t *);

/* cstm_alias.c */
int cstm_history(info_t *);
int cstm_alias(info_t *);

/*cstm_getline.c */
ssize_t read_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* cstmm_getinfo.c */
void info_clear(info_t *);
void info_set(info_t *, char **);
void info_free(info_t *, int);

/* cstm_environ.c */
char *cstm_getenv(info_t *, const char *);
int cstm_env(info_t *);
int cstm_setenv(info_t *);
int cstm_unsetenv(info_t *);
int populate_env_list(info_t *);

/* cstm_getenv.c */
char **get_env(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* cstm_history.c */
char *get_hist(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist(info_t *info, char *buf, int linecount);
int renumber_hist(info_t *info);

/* cstm_lists.c */
list_t *addnode_(list_t **, const char *, int);
list_t *addnode_end(list_t **, const char *, int);
size_t printlist_str(const list_t *);
int delete_node_index(list_t **, unsigned int);
void freelist_(list_t **);

/* cstm_lists1.c */
size_t listlen_(const list_t *);
char **list_to_str(list_t *);
size_t list_print(const list_t *);
list_t *nodestarts_with(list_t *, char *, char);
ssize_t getnode_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
