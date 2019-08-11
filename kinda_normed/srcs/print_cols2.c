/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cols2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:43:47 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/11 18:44:07 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		cols_output(t_dir *object, uint16_t ws_col, uint16_t total)
{
	t_col_tty	col_struct;
	char		buf[BUFF_MAX];
	uint16_t	count;
	uint16_t	curr_row;

	if (!object)
		exit(-1);
	total = 0;
	count = 0;
	col_struct = colstruct_info(object, ws_col);
	curr_row = 0;
	while (object && ++curr_row <= col_struct.rows)
	{
		create_print_buf(object, col_struct, buf, &count);
		object = object->next;
	}
	write(1, buf, count);
}
