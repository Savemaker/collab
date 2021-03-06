/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:32:14 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/11 18:33:45 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	define_mode(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISREG(mode))
		return ('-');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('?');
}

void	fillin_data(struct dirent *entry, t_dir *object,
	t_dir *file, t_dir **head)
{
	file->mode = DTTOIF(entry->d_type);
	file->name = ft_strdup(entry->d_name);
	file->path = check_path(object->path, entry->d_name);
	file->namewidth = entry->d_namlen;
	file->level = (object->level) + 1;
	if (check_flags(object->flags, 'l') || check_flags(object->flags, 't')
		|| check_flags(object->flags, 'u') || check_flags(object->flags, 'g')
			|| check_flags(object->flags, 'S'))
		if (!(get_data(file)))
			delete_from_root(&file, head);
}

t_dir	*get_data(t_dir *file)
{
	struct stat	buf;

	if (!(file))
		return (NULL);
	if (lstat((file)->path, &buf) == -1)
	{
		check_error((file)->path, (file)->name);
		return (NULL);
	}
	file->blocks = buf.st_blocks;
	file->uid = buf.st_uid;
	file->gid = buf.st_gid;
	file->nlink = buf.st_nlink;
	file->atime = buf.st_atime;
	file->mtime = buf.st_mtime;
	file->mode = buf.st_mode;
	if (define_mode((file)->mode) == 'b' || define_mode((file)->mode) == 'c')
		(file)->rdev = buf.st_rdev;
	else
		(file)->size = buf.st_size;
	return (file);
}

t_dir	*stat_info(t_dir **dir)
{
	struct stat	infobuf;

	if (!(*dir))
		return (NULL);
	if (lstat((*dir)->path, &infobuf) == -1)
	{
		check_error((*dir)->path, (*dir)->name);
		return (NULL);
	}
	(*dir)->mode = infobuf.st_mode;
	(*dir)->uid = infobuf.st_uid;
	(*dir)->gid = infobuf.st_gid;
	(*dir)->nlink = infobuf.st_nlink;
	(*dir)->atime = infobuf.st_atime;
	(*dir)->mtime = infobuf.st_mtime;
	if (define_mode((*dir)->mode) == 'b' || define_mode((*dir)->mode) == 'c')
		(*dir)->rdev = infobuf.st_rdev;
	else
		(*dir)->size = infobuf.st_size;
	return (*dir);
}
