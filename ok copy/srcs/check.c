#include "ft_ls.h"

void check_error(char *dpath, char *name) //this
{
	if (errno == 13) //Permission denied
	{
		ft_putstr("\n");
		ft_putstr(dpath);
		ft_putstr("\nft_ls: ");
		perror(name);
	}
	else
	{
		ft_putstr("ft_ls: ");
		perror(dpath);
	}
}

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
		ft_memdel((void **)&tmp);
	}
	return (full);
}

char	*check_name_from_path(char *name)
{
	if (!(ft_strrchr(name, '/')))
		return (ft_strdup(name));
	else
		return(ft_strdup(ft_strrchr(name, '/') + 1)); //ориентируется на первое вхождение / и дублирует со след символа
}
