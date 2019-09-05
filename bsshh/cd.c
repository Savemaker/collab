#include "minishell.h"

void launch_cd(char *path)
{
	struct stat s;

	if (path[0] == ' ')
		path = getenv_cmnd("HOME");
	if (path && !access(path, F_OK))
	{
		if ((stat(path, &s)) == -1)
			perror_cmnd("minishell", NULL, STATERR);
		else if (!S_ISDIR(s.st_mode))
			perror_cmnd("cd", path, NOTDIR);
		else if (access(path, R_OK))
			perror_cmnd("minishell", path, 0);
		else
		if (chdir(path) == -1)
			perror_cmnd("cd", path, CHDIRERR);
	}
	else
		perror_cmnd("cd", path, NOFLODIR);
}

void check_cd(int argc, char **args)
{
	char *path;

	if (argc == 1 || !ft_strcmp(args[1], "--") || !ft_strcmp(args[1], "~"))
	{
		if (!(path = getenv_cmnd("HOME")))
			return;
	}
	else if (!ft_strcmp(args[1], "."))
		path = getenv("PWD");
	else if (!ft_strcmp(args[1], "-"))
	{
		path = getenv("OLDPWD");
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
	{
		if (!ft_strcmp(args[1], " ") && argc == 3)
			path = args[2];
		else
			path = args[1];
	}
	launch_cd(path);
}

int cd_cmnd(char **args)
{
	int argc;
	char dir_path[MAXDIR];
	char *pwd_path;

	argc = 0;
	while (args[argc])
		argc++;

	if (argc == 3)
	{
		if (!ft_strcmp(args[1], " "))
			check_cd(argc, args);

		else
			perror_cmnd("cd", args[1], NOTINPWD); //string not in pwd:

	}
	else if (argc > 3)
		perror_cmnd("cd", NULL, MNARGS); //too many arguments
	else
		check_cd(argc, args);
	if (!(getcwd(dir_path, MAXDIR)))
		perror_cmnd("cd", args[1], GETCWDERR);
	if ((pwd_path = getenv_cmnd("PWD")))
	{
		setenv_cmnd("OLDPWD", pwd_path);
		setenv_cmnd("PWD", dir_path);
	}
	return (1); // continue to execute
}