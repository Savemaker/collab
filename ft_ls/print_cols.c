/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cols.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 22:43:29 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 14:08:30 by bellyn-t         ###   ########.fr       */
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

t_dir		*next_obj(t_dir *obj, t_col_tty col_struct)
{
	ushort	i;

	i = 0;
	while (++i <= col_struct.rows && obj)
		obj = obj->next;
	return (obj);
}
