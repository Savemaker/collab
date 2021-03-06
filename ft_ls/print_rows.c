/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 21:36:46 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 17:36:36 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_rwstrct_info_dope(t_dir *object, t_row_tty *row_struct)
{
	acl_t		acl;

	if (listxattr(object->path, row_struct->xattr,
		ATTR_NAMESTR, XATTR_NOFOLLOW))
		row_struct->xattr_label_len = 1;
	if ((acl = acl_get_link_np(object->path, ACL_TYPE_EXTENDED)))
	{
		row_struct->xattr_label_len = 1;
		acl_free(acl);
	}
}

void		get_rowstruct_info(t_dir *object, t_row_tty *row_struct)
{
	uint16_t	len;
	size_t		strlen;

	row_struct->total += object->blocks;
	if ((len = get_sizelen(object->nlink)) > row_struct->nlink_len)
		row_struct->nlink_len = len;
	if ((strlen = ft_strlen(getpwuid(object->uid)->pw_name))
		> row_struct->uid_len)
		row_struct->uid_len = (uint16_t)strlen;
	if ((strlen = ft_strlen(getgrgid(object->gid)->gr_name))
		> row_struct->gid_len)
		row_struct->gid_len = (uint16_t)strlen;
	if (define_mode(object->mode) == 'b' || define_mode(object->mode) == 'c')
	{
		if ((len = get_sizelen(major(object->rdev))) > row_struct->major_len)
			row_struct->major_len = len;
		if ((len = get_sizelen(minor(object->rdev))) > row_struct->minor_len)
			row_struct->minor_len = len;
	}
	else if ((len = get_sizelen((int)object->size)) > row_struct->size_len)
		row_struct->size_len = len;
	get_rwstrct_info_dope(object, row_struct);
}

t_row_tty	rowstruct_info(t_dir *object)
{
	t_row_tty	row_struct;

	row_struct.total = 0;
	row_struct.nlink_len = 0;
	row_struct.size_len = 0;
	row_struct.uid_len = 0;
	row_struct.gid_len = 0;
	row_struct.xattr_label_len = 0;
	row_struct.major_len = 0;
	row_struct.minor_len = 0;
	while (object)
	{
		get_rowstruct_info(object, &row_struct);
		object = object->next;
	}
	return (row_struct);
}

int			check_buf(char *buf, int i)
{
	if (i + 300 >= BUFF_MAX_ROW)
	{
		write(1, buf, i);
		ft_bzero(buf, BUFF_MAX_ROW);
		return (0);
	}
	return (i);
}

void		rows_output(t_dir *object, uint16_t ws_cols, uint16_t total)
{
	t_row_tty	row_struct;
	char		buf[BUFF_MAX_ROW];
	uint16_t	count;

	ws_cols = 0;
	ft_bzero(buf, BUFF_MAX_ROW);
	count = 0;
	row_struct = rowstruct_info(object);
	if (total)
		print_total(&row_struct);
	while (object)
	{
		count = check_buf(buf, count);
		count += print_attributes(object, buf + count, &row_struct, 0);
		object = object->next;
	}
	write(1, buf, (size_t)count);
}
