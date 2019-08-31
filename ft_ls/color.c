/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:24:16 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 14:06:20 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		make_colorful(char *color, char *buf)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (color[c])
		buf[i++] = color[c++];
	return (i);
}

char	*assign_colour(int which)
{
	if (which == 1)
		return ("\e[91m");
	if (which == 2)
		return ("\e[96m");
	if (which == 3)
		return ("\e[95m");
	if (which == 4)
		return ("\e[43m\e[30m");
	if (which == 5)
		return ("\e[44m");
	if (which == 6)
		return ("\e[106m");
	if (which == 7)
		return ("\e[35m");
	if (which == 8)
		return ("\e[42m");
	if (which == 9)
		return ("\e[33m");
	return (NULL);
}

int		color_name_dope(t_dir *object, char *buf, mode_t mode, int i)
{
	if ((define_mode(object->mode) == 'd') && (S_IWOTH & mode) == S_IWOTH)
		i = make_colorful(assign_colour(9), buf);
	if (((S_ISVTX & object->mode) == S_ISVTX)
		&& (S_IWOTH & mode) == S_IWOTH)
		i = make_colorful(assign_colour(8), buf);
	return (i);
}

int		color_name(t_dir *object, char *buf)
{
	int			i;
	struct stat s;

	i = 0;
	lstat(object->path, &s);
	if ((S_IXUSR & s.st_mode) == S_IXUSR || ((S_IXGRP & s.st_mode) == S_IXGRP)
		|| ((S_IXOTH & s.st_mode) == S_IXOTH))
		i = make_colorful(assign_colour(1), buf);
	if (define_mode(object->mode) == 'l')
		i = make_colorful(assign_colour(3), buf);
	if (define_mode(object->mode) == 'c')
		i = make_colorful(assign_colour(4), buf);
	if (define_mode(object->mode) == 'b')
		i = make_colorful(assign_colour(5), buf);
	if (define_mode(object->mode) == 'p')
		i = make_colorful(assign_colour(6), buf);
	if (define_mode(object->mode) == 's')
		i = make_colorful(assign_colour(7), buf);
	if (define_mode(object->mode) == 'd')
		i = make_colorful(assign_colour(2), buf);
	return (color_name_dope(object, buf, s.st_mode, i));
}

int		reset_color(char *buf, int background)
{
	char	*reset1;
	char	*reset2;
	int		c;
	int		i;

	reset1 = "\e[39m";
	reset2 = "\e[49m";
	i = 0;
	c = 0;
	if (background == 0)
		while (reset1[c])
			buf[i++] = reset1[c++];
	if (background == 1)
		while (reset2[c])
			buf[i++] = reset2[c++];
	if (background == 2)
	{
		while (reset1[c])
			buf[i++] = reset1[c++];
		c = 0;
		while (reset2[c])
			buf[i++] = reset2[c++];
	}
	return (i);
}
