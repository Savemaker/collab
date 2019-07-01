#include "ft_ls.h"

DIR *check_open(char *dpath, char *name)
{
	DIR *dir;

	dir = opendir(dpath);
	if (dir == NULL)
	{
		check_error(dpath, name);
		return (NULL);
	}
	return (dir);
}

void check_close(int ret)
{
	if (ret == -1)
	{
		perror("ft_ls");
		exit(-1);
	}
}

void check_error(char *dpath, char *name)
{
	if (errno == 13) //Permission denied
	{

		ft_putstr("ft_ls: ");
		perror(name);
	}
	else
	{
		ft_putstr("ft_ls: ");
		perror(dpath);
	}
}

char	**check_dir(int argc, char **argv, int flags_quantity)
{

	if (argc - flags_quantity == 1)
	{
		argv[argc] = ".";
		argv[argc + 1] = NULL;
	}
	return (argv);
}

void	usage_msg(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ls [-GRadfglrtu] [file ...]\n");
	exit(-1);
}

char	*check_name_from_path(char *name)
{
	if (!(ft_strrchr(name, '/')))
		return (ft_strdup(name));
	else
		return(ft_strdup(ft_strrchr(name, '/') + 1)); //ориентируется на первое вхождение / и дублирует со след символа
}

char	*check_path(char *path, char *name)
{
	char	*full;
	char	*tmp;

	if (path[ft_strlen(path) - 1] == '/')
		return (ft_strjoin(path, name));
	else
	{
		tmp = ft_strjoin(path, "/");
		full = ft_strjoin(tmp, name);
        //delete tmp
	}
	return (full);
}