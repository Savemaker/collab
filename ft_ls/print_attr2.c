/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_attr2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 21:49:03 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 14:08:10 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			print_uid(uid_t uid, char *buf, t_row_tty **row_struct)
{
	int				i;
	struct passwd	*psw;

	i = 0;
	psw = getpwuid(uid);
	while (psw->pw_name[i])
	{
		buf[i] = psw->pw_name[i];
		i++;
	}
	while (i < (*row_struct)->uid_len + 2)
		buf[i++] = ' ';
	return (i);
}

int			print_gid(gid_t gid, char *buf, t_row_tty **row_struct)
{
	int				i;
	struct group	*g;

	i = 0;
	g = getgrgid(gid);
	while (g->gr_name[i])
	{
		buf[i] = g->gr_name[i];
		i++;
	}
	while (i < (*row_struct)->gid_len + 2)
		buf[i++] = ' ';
	return (i);
}

int			check_six_months(time_t stm)
{
	time_t now;
	time_t dif;

	now = time(NULL);
	dif = now - stm;
	if (dif > 86400 * 182)
		return (1);
	return (0);
}

int			check_future(time_t obj_time)
{
	time_t now;

	now = time(NULL);
	if (obj_time > now)
		return (1);
	return (0);
}

int			print_time(char *buf, t_dir *list)
{
	char	*time;
	int		i;
	int		off;

	off = 0;
	i = 4;
	time = ctime(&(list->mtime));
	while (i < 11)
		buf[off++] = time[i++];
	if (check_six_months(list->mtime) || check_future(list->mtime))
	{
		buf[off++] = ' ';
		i = 20;
		while (i < 24)
			buf[off++] = time[i++];
	}
	else
		while (i < 16)
			buf[off++] = time[i++];
	buf[off++] = ' ';
	return (off);
}
