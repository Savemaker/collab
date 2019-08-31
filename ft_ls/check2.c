/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:37:51 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 14:05:48 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		**check_dir(int argc, char **argv, int flags_quantity)
{
	if (argc - flags_quantity == 1)
	{
		argv[argc] = ".";
		argv[argc + 1] = NULL;
	}
	return (argv);
}

void		check_dope(mode_t mode, char *buf)
{
	if ((S_IRWXO & mode) != S_IRWXO)
	{
		if ((S_IROTH & mode) != S_IROTH)
			buf[6] = '-';
		if ((S_IWOTH & mode) != S_IWOTH)
			buf[7] = '-';
		if ((S_IXOTH & mode) != S_IXOTH)
			buf[8] = '-';
	}
	if ((S_ISVTX & mode) == S_ISVTX)
		buf[8] = 't';
}

void		check_access(mode_t mode, char *buf)
{
	if ((S_IRWXU & mode) != S_IRWXU)
	{
		if ((S_IRUSR & mode) != S_IRUSR)
			buf[0] = '-';
		if ((S_IWUSR & mode) != S_IWUSR)
			buf[1] = '-';
		if ((S_IXUSR & mode) != S_IXUSR)
			buf[2] = '-';
	}
	if ((S_IRWXG & mode) != S_IRWXG)
	{
		if ((S_IRGRP & mode) != S_IRGRP)
			buf[3] = '-';
		if ((S_IWGRP & mode) != S_IWGRP)
			buf[4] = '-';
		if ((S_IXGRP & mode) != S_IXGRP)
			buf[5] = '-';
	}
	check_dope(mode, buf);
}
