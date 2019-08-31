/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_ft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 21:03:23 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 14:09:33 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint16_t	default_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) > 0)
		return (1);
	return (0);
}

uint16_t	reverse_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) < 0)
		return (1);
	return (0);
}

uint16_t	time_sort(t_dir *dir, t_dir *dira)
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

uint16_t	time_reverse_sort(t_dir *dir, t_dir *dira)
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

uint16_t	atime_sort(t_dir *dir, t_dir *dira)
{
	if (dir->atime > dira->atime)
		return (1);
	return (0);
}
