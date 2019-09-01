//
// Created by Екатерина on 2019-08-20.
//

#include "../includes/minishell.h"

//#include <sys/errno.h>

char *check_error_code(int error_code)
{
	if (error_code == 1)
		return (": string not in pwd: ");
	if (error_code == 2)
		return (": too many arguments");
	if (error_code == 3)
		return (": gwtcwd() error");
	if (error_code == 5)
		return (": stat() error");
	if (error_code == 4)
		return (": lstat() error");
	if (error_code == 6)
		return (": command not found: ");
	if (error_code == 7)
		return (": execve() error");
	if (error_code == 8)
		return (": fork() error");
	if (error_code == 9)
		return (": malloc() error");
	if (error_code == 10)
		return (": not a directory: ");
	if (error_code == 11)
		return (": chdir() error: ");
	if (error_code == 12)
		return (": setenv() error");
	return (NULL);
}

void perror_cmnd(char *cmnd, char *error_path, int error_code)
{

	ft_putstr_fd(cmnd, STDOUT_FILENO);
	if (error_code != 0)
		ft_putstr(check_error_code(error_code));
	else
		ft_putstr_fd(" :", STDOUT_FILENO);
	if (error_path)
		ft_putstr_fd(error_path, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}