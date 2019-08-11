/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_ft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:48:45 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/11 18:50:12 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		default_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) > 0)
		return (1);
	return (0);
}

int		reverse_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) < 0)
		return (1);
	return (0);
}

int		time_sort(t_dir *dir, t_dir *dira)
{
	struct stat s;
	struct stat sa;
	time_t		d;
	time_t		da;

	lstat(dir->path, &s);
	lstat(dira->path, &sa);
	d = s.st_mtime;
	da = sa.st_mtime;
	if (d < da)
		return (1);
	if (d == da)
		if (ft_strcmp(dir->name, dira->name) > 0)
			return (1);
	return (0);
}

int		time_reverse_sort(t_dir *dir, t_dir *dira)
{
	struct stat s;
	struct stat sa;
	time_t		d;
	time_t		da;

	lstat(dir->path, &s);
	lstat(dira->path, &sa);
	d = s.st_mtime;
	da = sa.st_mtime;
	if (d > da)
		return (1);
	if (d == da)
	{
		if (ft_strcmp(dir->name, dira->name) < 0)
			return (1);
	}
	return (0);
}

int		size_sort(t_dir *dir, t_dir *dira)
{
	if (dir->size < dira->size)
		return (1);
	return (0);
}

int		atime_sort(t_dir *dir, t_dir *dira)
{
	if (dir->atime > dira->atime)
		return (1);
	return (0);
}
