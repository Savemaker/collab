#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
//#include "get_next_line.h"

# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
#include <stdio.h>
# include <sys/dir.h>

# define BUFF_SIZE 1000

#define NOTINPWD 1
#define MNARGS 2
#define GETCWDERR 3
#define LSTATERR 4
#define STATERR 5
#define CMNDNTFND 6
#define EXECVEERR 7
#define FORKERR 8
#define MLKERR 9
#define NOTDIR 10
#define CHDIRERR 11
#define SETENVERR 12

#define MAXDIR 4095

int g_sig;

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define SHELL_NAME "\e[95m\e[1mminishell\e[0m🌚 "

#define LINE_BUFSIZE 1024
//int get_val_index(char *name);

int cd_cmnd(char **args);
//int check_setenv(char **env);
void print_env(char **env);
int env_cmnd();


int echo_cmnd(char **args);
int exit_cmnd();

char	*getenv_cmnd(char *name);
char **make_env_cp(char **env_dst, char **env_origin);


int		str_quantity();
int unsetenv_cmnd(char *name);
char **g_env;
int setenv_cmnd(char *name, char *value);

void perror_cmnd(char *cmnd, char *error_path, int error_code);
char *check_error_code(int error_code);
char	**split_cmnd(char const *s, char c);



int		check_existenv(const char *name, char *request);

int		get_envindex(const char *name);
int checkenv(char *envstr);



int		count_pointers(char **envp);
void	free_copy_envp(char ***envp);
#endif
