#include "ft_ls.h"

void	get_rowstruct_info(t_dir *object, t_row_tty *row_struct)
{
	uint16_t len;
	size_t strlen;

	row_struct->total += object->blocks;
	if ((len = get_sizelen(object->nlink)) > row_struct->nlink_len)
		row_struct->nlink_len = len;
	if ((strlen = ft_strlen(getpwuid(object->uid)->pw_name)) > row_struct->uid_len)
		row_struct->uid_len = (uint16_t)strlen;
	if ((strlen = ft_strlen(getgrgid(object->gid)->gr_name)) > row_struct->gid_len)
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
	if (listxattr(object->path, row_struct->xattr, ATTR_NAMESTR, XATTR_NOFOLLOW) || acl_get_link_np(object->path, ACL_TYPE_EXTENDED)) //@ //+?
		row_struct->xattr_label_len = 1;
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

int check_dynamicbf(int count, char *buf)
{
	if (count == (uint16_t)BUFF_MAX)
	{
		write(1, buf, (size_t)count);
		count = 0;
		ft_bzero(buf, BUFF_MAX);
	}
	return (count);
}

void		rows_output(t_dir *object, uint16_t ws_cols, uint16_t total)
{
	t_row_tty row_struct;
//	char buf[BUFF_MAX];
	char *buf;
//	uint16_t count;
	int count;

	ws_cols = 0; //unused((((
	buf = (char *)malloc(sizeof(char) * BUFF_MAX);
	// ft_bzero(buf, BUFF_MAX);


	count = 0;
	row_struct = rowstruct_info(object);
	if (total)
		print_total(&row_struct);
	while (object)
	{
//		count = 0;


		count = print_attributes(object, buf, &row_struct, count);
		object = object->next;
//		count += print_attributes(object, buf + count, &row_struct);
////		check_buf(buf, count);
//	check_dynamicbf(count, buf);
////		if (count + 300 >= (uint16_t)BUFF_MAX)
////		{
////			write(1, buf, (size_t)count);
////			count = 0;
////			ft_bzero(buf, BUFF_MAX);
////		}
//		object = object->next;
	}
	write(1, buf, (size_t)count);
}