/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 17:50:36 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/11 17:53:33 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		identify(t_dir *dirlst, char *name)
{
	dirlst->name = check_name_from_path(name);
	dirlst->namewidth = (uint16_t)ft_strlen(name);
	dirlst->path = ft_strdup(name);
}

t_dir		*make_argv_lst(char **argv, uint16_t flags, uint16_t *i)
{
	t_dir *root;
	t_dir *dir;
	t_dir *filelst;

	dir = NULL;
	root = dir;
	filelst = NULL;
	while (argv[++(*i)])
	{
		dir = checkroot_andcreate(dir, &root, flags);
		identify(dir, argv[*i]);
		if (!(stat_info(&dir)))
		{
			delete_from_root(&dir, &root);
			continue;
		}
		if (define_mode(dir->mode) != 'd' && !(check_flags(flags, 'd')))
			dir = make_list(dir, &filelst, &root);
	}
	return (display_files(root, filelst));
}

t_dir		*make_list(t_dir *object, t_dir **file_head, t_dir **root)
{
	t_dir	*tmp;

	if (!(*file_head))
	{
		*file_head = object;
		(*file_head)->prev = NULL;
	}
	else
	{
		tmp = *file_head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = object;
		object->prev = tmp;
	}
	return (mount_file(object, root));
}

t_dir		*dir_reading(t_dir *object)
{
	t_dir			*head;
	t_dir			*file;
	struct dirent	*entry;
	DIR				*dir;

	if (define_mode(object->mode) != 'd' ||
		!(dir = check_open(object->path, object->name)))
		return (NULL);
	file = NULL;
	head = file;
	while ((entry = readdir(dir)) != NULL)
	{
		if ((!(check_flags(object->flags, 'a'))
			&& !(check_flags(object->flags, 'f')))
				&& (entry->d_name)[0] == '.')
			continue ;
		file = checkroot_andcreate(file, &head, object->flags);
		fillin_data(entry, object, file, &head);
	}
	check_close(closedir(dir));
	return (head);
}
