/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pizdo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 22:49:07 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 14:11:11 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		create_print_buf(t_dir *object, t_col_tty col_struct,
char *buf, int *count)
{
	uint16_t curr_col;
	uint16_t j;

	curr_col = 0;
	while (++curr_col <= col_struct.cols && object)
	{
		j = 0;
		*count += color_name(object, buf + *count);
		while (object->name[j])
			buf[(*count)++] = object->name[j++];
		if ((define_mode(object->mode) != 'c'
		&& (S_ISVTX & object->mode) != S_ISVTX)
		&& (define_mode(object->mode) != 'b')
		&& (define_mode(object->mode) != 'p'))
			*count += reset_color(buf + *count, 0);
		else
			*count += reset_color(buf + *count, 1);
		while (j++ <= col_struct.maxwidth && curr_col != col_struct.cols)
			buf[(*count)++] = ' ';
		object = next_obj(object, col_struct);
	}
	buf[(*count)++] = '\n';
}

int			print_size(long int size, char *buf, long int max_len)
{
	int			i;
	long int	len;

	i = 0;
	len = get_sizelen((int)size);
	while (i + len < max_len)
		buf[i++] = ' ';
	nbtostr(size, (int)(i + len - 1), buf);
	buf[i + len] = ' ';
	return ((int)max_len + 1);
}
