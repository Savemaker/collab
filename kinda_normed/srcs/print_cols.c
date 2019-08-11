/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cols.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:41:40 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/11 18:43:26 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		set_cols(t_col_tty *col_struct)
{
	uint16_t quantity;

	quantity = col_struct->obj_quantity;
	if (quantity % col_struct->rows == 0)
		col_struct->cols = quantity / col_struct->rows;
	else
		col_struct->cols = quantity / col_struct->rows + (uint16_t)1;
}

void		set_cols_plus(t_col_tty *col_struct)
{
	uint16_t quantity;

	quantity = col_struct->obj_quantity;
	if (quantity % ++(col_struct->rows) == 0)
		col_struct->cols = quantity / col_struct->rows;
	else
		col_struct->cols = quantity / col_struct->rows + (uint16_t)1;
}

void		define_cols_rows(t_col_tty *col_struct, uint16_t ws_col)
{
	uint16_t quantity;
	uint16_t maxwidth;

	quantity = col_struct->obj_quantity;
	maxwidth = col_struct->maxwidth;
	col_struct->cols = quantity;
	col_struct->rows = 1;
	if (maxwidth >= ws_col)
	{
		col_struct->cols = quantity / col_struct->rows;
		col_struct->rows = quantity;
		return ;
	}
	while (((maxwidth + 1) * quantity) / col_struct->rows > ws_col)
		(col_struct->rows)++;
	set_cols(col_struct);
	while (col_struct->cols * (maxwidth + 1) > ws_col)
		set_cols_plus(col_struct);
}

t_col_tty	colstruct_info(t_dir *object, uint16_t ws_col)
{
	t_col_tty	col_struct;

	col_struct.maxwidth = 0;
	col_struct.obj_quantity = 0;
	while (object)
	{
		if (object->namewidth > col_struct.maxwidth)
			col_struct.maxwidth = object->namewidth;
		object = object->next;
		col_struct.obj_quantity++;
	}
	define_cols_rows(&col_struct, ws_col);
	return (col_struct);
}

uint16_t	check_buf(char *buf, uint16_t i)
{
	if (i == (uint16_t)BUFF_MAX)
	{
		write(1, buf, i);
		return (0);
	}
	return (i);
}

t_dir		*next_obj(t_dir *obj, t_col_tty col_struct)
{
	ushort	i;

	i = 0;
	while (++i <= col_struct.rows && obj)
		obj = obj->next;
	return (obj);
}

void		create_print_buf(t_dir *object, t_col_tty col_struct,
	char *buf, uint16_t *count)
{
	uint16_t curr_col;
	uint16_t j;

	curr_col = 0;
	while (++curr_col <= col_struct.cols && object)
	{
		j = 0;
		while (object->name[j])
		{
			*count = check_buf(buf, *count);
			buf[(*count)++] = object->name[j++];
		}
		while (j++ <= col_struct.maxwidth && curr_col != col_struct.cols)
		{
			*count = check_buf(buf, *count);
			buf[(*count)++] = ' ';
		}
		object = next_obj(object, col_struct);
	}
	*count = check_buf(buf, *count);
	buf[(*count)++] = '\n';
}
