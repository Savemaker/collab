/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_attr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:22:21 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/11 19:22:22 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			print_access(t_dir *object, char *buf, t_row_tty *row_struct)
{
	int	i;
	acl_t acl;

	i = 0;
	acl = NULL;
	while (i < 8)
	{
		buf[i++] = 'r';
		buf[i++] = 'w';
		buf[i++] = 'x';
	}
	check_access(object->mode, buf);
	if (define_mode(object->mode) != 'b' && define_mode(object->mode) != 'c' && (row_struct->xattr_lstsize = listxattr(object->path, row_struct->xattr, ATTR_NAMESTR, XATTR_NOFOLLOW) > 0))
		buf[i++] = '@';
	else if (define_mode(object->mode) != 'b' && define_mode(object->mode) != 'c' && (acl = acl_get_link_np(object->path, ACL_TYPE_EXTENDED)))
	{
		buf[i++] = '+';
		acl_free(acl);
	}
	while (i < (*row_struct).xattr_label_len + 10)
		buf[i++] = ' ';
	return (i + row_struct->xattr_label_len);
}

void		print_total(t_row_tty *row_struct)
{
	ft_putstr("total ");
	ft_putnbr(row_struct->total);
	ft_putchar('\n');
}

int			color_name(t_dir *object, char *buf)
{
	char *color;
	int i;
	int c;

	i = 0;
	c = 0;
	if (define_mode(object->mode) == 'd')
	{
		color = "\e[96m";
		while (color[c])
			buf[i++] = color[c++];
	}
	if (define_mode(object->mode) == 'l')
	{
		color = "\e[95m";
		while (color[c])
			buf[i++] = color[c++];
	}
	return (i);
}

int			print_name(t_dir *object, char *buf)
{
	int i;
	char link[1024];
	ssize_t ret;
	char *pointer;
	char *reset;
	int j;
	int c;
	int x;

	x = 0;
	c = 0;
	j = 0;
	i = 0;
	pointer = " -> ";
	reset = "\e[39m";
	i = color_name(object, buf);
	while (object->name[x])
	{
		buf[i] = object->name[x];
		i++;
		x++;
	}
	c = 0;
	while (reset[c])
			buf[i++] =  reset[c++];
	if ((define_mode(object->mode) == 'l'))
	{
		if (!(ret = readlink(object->path, link, 1024))) //tut бы ошибку обработать но лень правилньо
			check_error(object->path, object->name);
		else
		{
			link[ret] = '\0';
			while (pointer[j])
				buf[i++] = pointer[j++];
			j = 0;
			while (link[j])
				buf[i++] = link[j++];
			buf[i++] = '\n';
		}
	}
	else
		buf[i++] = '\n';
	return (i);
}

int			print_size(long int size, char *buf, long int max_len)
{
	int i;
	long int len;

	i = 0;
	len = get_sizelen((int)size);
	while (i + len < max_len)
		buf[i++] = ' ';
	nbtostr(size, (int)(i + len - 1), buf);
	buf[i + len] = ' ';
	return ((int)max_len + 1);
}

int			print_major_minor(long int size, char *buf, long int max_len, uint16_t major)
{

	int i;
	long int len;

	i = 0;
	len = get_sizelen((int)size);
	while (i + len < max_len)
		buf[i++] = ' ';
	if (major)
		max_len = max_len + (uint16_t)2;
	nbtostr(size, (int)(i + len - 1), buf);
	if (major)
		buf[i++ + len] = ',';
	buf[i + len] = ' ';
	return ((int)max_len + 1);
}