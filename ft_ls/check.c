/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:24:30 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 17:47:23 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_error(char *dpath, char *name)
{
	if (errno == 13)
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

DIR		*check_open(char *dpath, char *name)
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

void	check_close(int ret)
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
		return (ft_strdup(ft_strrchr(name, '/') + 1));
}
