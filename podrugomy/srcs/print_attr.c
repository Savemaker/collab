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

int print_link(t_dir *object, char *buf)
{
	char link[1024];
	ssize_t ret;
	char *pointer;
	int i;
	int j;

	i = 0;
	j = 0;
	pointer = " -> ";
	if (!(ret = readlink(object->path, link, 1024)))
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
	return (i);
}

int			print_name(t_dir *object, char *buf)
{
	int i;
	int c;

	i = color_name(object, buf);
	c = 0;
	while (object->name[c])
		buf[i++] = object->name[c++];
	if ((define_mode(object->mode) != 'c' && (S_ISVTX & object->mode) != S_ISVTX) && (define_mode(object->mode) != 'b') && (define_mode(object->mode) != 'p'))
		i += reset_color(buf + i, 0);
	else
		i += reset_color(buf + i, 1);
	if ((define_mode(object->mode) == 'l'))
		i += print_link(object, buf + i);
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