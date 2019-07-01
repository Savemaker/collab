#include "ft_ls.h"

void		print_total(t_row_tty *row_struct)
{
	ft_putstr("total ");
	ft_putnbr(row_struct->total);
	ft_putchar('\n');
}

void 		check_access(mode_t mode, char *buf)
{
	if ((S_IRWXU & mode) != S_IRWXU) //for owner
	{
		if ((S_IRUSR & mode) != S_IRUSR) //4
			buf[0] = '-';
		if ((S_IWUSR & mode) != S_IWUSR) //2
			buf[1] = '-';
		if ((S_IXUSR & mode) != S_IXUSR) //1
			buf[2] = '-';
	}
	if ((S_IRWXG & mode) != S_IRWXG) //for group
	{
		if ((S_IRGRP & mode) != S_IRGRP)
			buf[3] = '-';
		if ((S_IWGRP & mode) != S_IWGRP)
			buf[4] = '-';
		if ((S_IXGRP & mode) != S_IXGRP)
			buf[5] = '-';
	}
	if ((S_IRWXO & mode) != S_IRWXO) //for other
	{
		if ((S_IROTH & mode) != S_IROTH)
			buf[6] = '-';
		if ((S_IWOTH & mode) != S_IWOTH)
			buf[7] = '-';
		if ((S_IXOTH & mode) != S_IXOTH)
			buf[8] = '-';
	}
}

int			print_access(mode_t mode, const char *path, char *buf)
{
	int	i;
	char attr[1024];
	size_t res;

	res = 0;
	i = 0;
	while (i < 8)
	{
		buf[i++] = 'r';
		buf[i++] = 'w';
		buf[i++] = 'x';
	}
	check_access(mode, buf);
	res = listxattr(path, attr, 1024, XATTR_NOFOLLOW);
	if (res > 0)
		buf[i] = '@';
	return (10);
}

int			print_name(t_dir *object, char *buf)
{
	int i;
	char link[2048];
	size_t ret;
	int c;

	i = 0;
	c = 0;
	while (object->name[i])
	{
		buf[i] = object->name[i];
		i++;
	}
	if ((define_mode(object->mode) == 'l'))
	{
		ret = readlink(object->path, link, 1024);  //tut бы ошибку обработать но лень правилньо
		if (ret > 0)  
		{
			link[ret] = '\0';
			buf[i++] = '-';
			buf[i++] = '>';
			while (link[c])
				buf[i++] = link[c++];
			buf[i++] = '\n';
		}                            
	}
	else
		buf[i++] = '\n';
	
	return (i);
}

int print_nlink(nlink_t link, char *buf)
{
	int i;
	char *str;
	i = 0;
	int j;
	j = 0;

	j = ft_strlen(str = ft_itoa(link));
	while (j-- )
	{
		buf[i] = str[i];
		i++;
	}
	buf[i] = '\n';
	return (i);
}

int			print_uid(uid_t uid, char *buf) {
	int i;
	struct passwd *psw;

	i = 0;
	psw = getpwuid(uid);
	while (psw->pw_name[i]) {
		buf[i] = psw->pw_name[i];
		i++;
	}
	buf[i] = '\n';
	return (i);
}

int 		print_gid(gid_t gid, char *buf)
{
	int i;
	struct group *g;

	i = 0;
	g = getgrgid(gid);
	while (g->gr_name[i])
	{
		buf[i] = g->gr_name[i];
		i++;
	}
	buf[i] = '\n';
	return (i);
}

int			print_size(off_t size, char *buf)
{
	char *str;
	int i;
	int j;

	i = 0;
	j = 0;
	j = ft_strlen(str = ft_itoa(size));
	while (j--)
	{
		buf[i] = str[i];
		i++;
	}
	buf[i] = '\n';
	return (i);
}

int			print_time(time_t time, char *buf)
{
	int i;
	int j;
	int c;
	char *str;

	c = 4;
	i = 0;
	j = ft_strlen(str = ctime(&time)) - 9;
	while (j-- > 4)
	{
		buf[i] = str[c];
		c++;
		i++;
	}
	buf[i] = '\n';
	return (i);
}

int			print_attributes(t_dir *object, char *buf)
{
	int		i;

	i = 0;
	buf[i] = define_mode(object->mode);
	i++;
	i += print_access(object->mode, object->path, buf + i);
	i += print_nlink(object->nlink, buf +i );
//	if (define_mode(object->mode) == 'l')
	//	i += print_link(object, buf + i);
	//владеле
	i += print_uid(object->uid, buf+i);
	if (!(check_flags(object->flags, 'g')))
		i += print_gid(object->gid, buf+i);
	//группа
	//размер в байтах
	i += print_size(object->size, buf+i);
	//i+= print_time() //аббревиатура месяца день час минута
	i += print_time(object->mtime, buf + i);
	i += print_name(object, buf + i);
	return (i);
}

//void	get_rowstruct_info(t_dir *object, t_row_tty *row_struct)
//{
//	//собрать инфу по ссылкам, тотал и тп
//}

t_row_tty	rowstruct_info(t_dir *object)
{
	t_row_tty	row_struct;

	row_struct.total = 0;
	row_struct.nlink = 0;
	row_struct.size = 0;
	row_struct.uid = 0;
	row_struct.gid = 0;
	row_struct.mtime = 0;
	while (object)
	{
		//get_rowstruct_info(object, &row_struct);
		object = object->next;
	}
	return (row_struct);
}

void		rows_output(t_dir *object, uint16_t ws_cols)
{
	t_row_tty	row_struct;
	char		buf[BUFF_MAX];
	int			count;

	ws_cols = 0; //unused((((
	count = 0;
	row_struct = rowstruct_info(object);
//	if something ???
//	print_total(&row_struct);

	while (object)
	{
		//снова нужно сделать чек на буфер, распечатать, если надо, count = 0
		count += print_attributes(object, buf + count);
		object = object->next;
	}
	write(1, buf, (size_t)count);
}