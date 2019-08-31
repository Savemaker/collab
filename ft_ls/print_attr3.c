/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_attr3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 22:03:45 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 14:11:30 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			print_xattr(t_dir *object, char *buf, t_row_tty *row_struct)
{
	ssize_t	j;
	int		i;
	ssize_t	val_len;
	char	value[ATTR_VALSIZE];
	char	*xattrstr;

	i = 0;
	j = 0;
	xattrstr = row_struct->xattr;
	while (j < row_struct->xattr_lstsize)
	{
		val_len = getxattr(object->path, row_struct->xattr + j, value,
		ATTR_VALSIZE, 0,
		(define_mode(object->mode) == 'l') ? XATTR_NOFOLLOW : 0);
		buf[i++] = '\t';
		while (xattrstr[j])
			buf[i++] = xattrstr[j++];
		buf[i++] = '\t';
		buf[i++] = ' ';
		buf[i++] = ' ';
		i += print_size(val_len, buf + i, 3);
		buf[i++] = '\n';
		j++;
	}
	return (i);
}

int			print_eflag_content(char *res, char *buf)
{
	t_word *str;

	str = (t_word *)(malloc(sizeof(t_word)));
	str->i = draw_zero(buf);
	str->j = 0;
	while (res[str->j] != '\n')
		str->j++;
	draw_word(res, buf, str);
	str->j++;
	buf[(str->i)++] = ':';
	skip_word(res, str);
	draw_word(res, buf, str);
	buf[(str->i)++] = ' ';
	str->j++;
	skip_word(res, str);
	draw_word(res, buf, str);
	buf[(str->i)++] = ' ';
	while (res[++(str->j)])
		buf[(str->i)++] = res[str->j];
	free(str);
	return (str->i);
}

int			print_flag_e(t_dir *object, char *buf)
{
	int		i;
	acl_t	acl;
	char	*res;
	ssize_t len;

	i = 0;
	acl = acl_get_link_np(object->path, ACL_TYPE_EXTENDED);
	res = acl_to_text(acl, &len);
	if (res != NULL)
		i = print_eflag_content(res, buf);
	acl_free(acl);
	return (i);
}

int			print_major_dope(t_dir *object, char *buf, t_row_tty *row_struct,
int i)
{
	i += print_major_minor((major(object->rdev)),
	buf + i, (long int)row_struct->major_len, 1);
	i += print_major_minor((minor(object->rdev)),
	buf + i, (long int)row_struct->minor_len, 0);
	return (i);
}

int			print_attributes(t_dir *object, char *buf,
	t_row_tty *row_struct, int i)
{
	buf[i] = define_mode(object->mode);
	i++;
	i += print_access(object, buf + i, row_struct);
	i += print_size((long int)object->nlink, buf + i,
	(long int)row_struct->nlink_len);
	if (!(check_flags(object->flags, 'g')))
		i += print_uid(object->uid, buf + i, &row_struct);
	i += print_gid(object->gid, buf + i, &row_struct);
	if (define_mode(object->mode) == 'b' || define_mode(object->mode) == 'c')
		i += print_major_dope(object, buf, row_struct, i);
	else if ((row_struct->minor_len > 0 || row_struct->major_len > 0))
		i += print_size((long int)object->size, buf + i,
		(long int)(row_struct->size_len
		+ row_struct->major_len + row_struct->minor_len + 1));
	else
		i += print_size((long int)object->size, buf + i,
		(long int)(row_struct->size_len));
	i += print_time(buf + i, object);
	i += print_name(object, buf + i);
	if (check_flags(object->flags, '@') && row_struct->xattr_lstsize)
		i += print_xattr(object, buf + i, row_struct);
	if (check_flags(object->flags, 'e'))
		i += print_flag_e(object, buf + i);
	return (i);
}
