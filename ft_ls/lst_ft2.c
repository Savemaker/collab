/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ft2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:37:00 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 14:07:15 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*create_new_node(uint16_t flags)
{
	t_dir	*lst;

	if (!(lst = (t_dir *)malloc(sizeof(t_dir))))
	{
		perror("ft_ls");
		exit(-1);
	}
	lst->inside_files = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	lst->name = NULL;
	lst->path = NULL;
	lst->flags = flags;
	lst->blocks = 0;
	lst->namewidth = 0;
	lst->gid = 0;
	lst->uid = 0;
	lst->mode = 0;
	lst->level = 1;
	lst->size = 0;
	lst->rdev = 0;
	lst->nlink = 0;
	lst->mtime = 0;
	lst->atime = 0;
	return (lst);
}

t_dir	*mount_file(t_dir *object, t_dir **root)
{
	t_dir	*root_obj;

	root_obj = *root;
	while (root_obj->next && define_mode(root_obj->next->mode) == 'd')
		root_obj = root_obj->next;
	if (!(root_obj->next))
	{
		object = NULL;
		*root = NULL;
	}
	else
	{
		object = root_obj;
		root_obj->next = NULL;
	}
	return (object);
}

t_dir	*checkroot_andcreate(t_dir *dir, t_dir **head, uint16_t flags)
{
	t_dir *new;

	if (!(*head))
	{
		dir = create_new_node(flags);
		*head = dir;
	}
	else
	{
		new = create_new_node(flags);
		dir->next = new;
		new->prev = dir;
		dir = new;
	}
	return (dir);
}
