/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 12:54:54 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/06/11 14:54:35 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	define_mode(mode_t mode)
{
	if (S_ISDIR(mode)) 			// папка мамка
		return ('d');
	else if (S_ISLNK(mode)) 	// символическая ссылка
		return ('l');
	else if (S_ISREG(mode)) 	// обычный файл
		return ('-');
	else if (S_ISCHR(mode)) 	// блочное устройство
		return ('c');
	else if (S_ISBLK(mode)) 	// символьное устройство
		return ('b');
	else if (S_ISFIFO(mode)) 	// юникс-канал или фифо-файл
		return ('p');
	else if (S_ISSOCK(mode)) 	// сокет
		return ('s');
	else
		return ('?');
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
	(*dir)->nlink =infobuf.st_nlink;
	(*dir)->atime = infobuf.st_atime;
	(*dir)->mtime = infobuf.st_mtime;
	if (define_mode((*dir)->mode) == 'b' || define_mode((*dir)->mode) == 'c')
		(*dir)->dev_type = infobuf.st_rdev;
	else
		(*dir)->size = infobuf.st_size;
	return (*dir);
}

int 	processing(int argc, char **argv)
{
	uint16_t flags;
	uint16_t flags_quantity;

	flags = add_flags(argv, &flags_quantity);
	argv = check_dir(argc, argv, flags_quantity); //если без аргументов, в качестве параметра лс отправляет точку
	print(make_argv_lst(argv, flags, &flags_quantity));
	return (1);
}

int		main(int argc, char **argv)
{
	if (!(processing(argc, argv)))
		exit(0); // возвращаемое значение? !чек!
	return (0);
}
