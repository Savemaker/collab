#include "ft_ls.h"


uint16_t			default_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) > 0)
		return (1);
	return (0);
}

uint16_t			reverse_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) < 0)
		return (1);
	return (0);
}
uint16_t time_sort(t_dir *dir, t_dir *dira)
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

uint16_t			time_reverse_sort(t_dir *dir, t_dir *dira)
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

uint16_t 		size_sort(t_dir *dir, t_dir *dira)
{
	if (dir->size < dira->size)
		return(1);
	return (0);
}

uint16_t atime_sort(t_dir *dir, t_dir *dira)
{
	if (dir->atime > dira->atime)
		return (1);
	return (0);
}
