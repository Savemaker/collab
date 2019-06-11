/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:14:44 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/23 16:24:02 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fill.h"
#include "../libft/libft.h"

int		check_desk_opportunity(t_mark *start, t_tetr *tetr, int desk_size)
{
	if ((start->row + tetr->height) <= desk_size && (start->col + tetr->width - col_brick_move(tetr)) <= desk_size)
		return (1);
	return (0);
}

int		col_brick_move(t_tetr *tetr)
{
	int i;

	i = 0;
	while (tetr->shape[0][i] == '.')
		i++;
	return (i);
}

int		blank(char **desk, t_mark *start, t_tetr *tetr, int desk_size)
{
	char	**shape;
	int		row;
	int		col;

	if (!(check_desk_opportunity(start, tetr, desk_size)))
		return (0);
	shape = tetr->shape;
	row = 0;
	while (shape[row] != NULL && row < tetr->height && (row + start->row) < desk_size)
	{
		col = 0;
		while (shape[row][col] != '\0' && col + start->col <= desk_size)
		{
			if (desk[row + start->row][col + start->col - col_brick_move(tetr)] != '.' && shape[row][col] != '.')
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

int		next_position(char **desk, t_mark *mark, t_tetr *tetr, int desk_size)
{
	mark->col = mark->col + 1;
	while (desk[mark->row] != NULL)
	{
		while (desk[mark->row][mark->col] != '\0')
		{
			if (desk[mark->row][mark->col] == '.' && check_desk_opportunity(mark, tetr, desk_size))
				return (1);
			mark->col++;
		}
		mark->row = mark->row + 1;
		mark->col = 0;
	}
	return (0);
}

int		solving(t_list *tetr_lst)
{
	char	**desk;
	int		fig_count;
	int		desk_size;
	t_mark	*start;

	fig_count = (int)(tetr_lst)->content_size;
	start = create_marks(0);
	desk_size = sizeof_desk(fig_count, tetr_lst);
	desk = draw_desk(desk_size);
	while (!(fillit(tetr_lst, desk, desk_size, start, fig_count)))
	{
		clean_desk(desk, desk_size);
		desk_size += 1;
		if (!(desk = draw_desk(desk_size)))
			return (0);
		start->row = 0;
		start->col = 0;
	}
	print_desk(desk);
	clean_desk(desk, desk_size);
	free(desk);
	return (1);
}

int		placing(char **desk, int desk_size, t_mark *start, t_tetr *tetr)
{
	int ok;

	while (!(ok = blank(desk, start, tetr, desk_size)))
	{
		if (!next_position(desk, start, tetr, desk_size))
			return (0);
	}
	return (ok);
}

char		**fillit(t_list *tetr_lst, char **desk, int desk_size, t_mark *start, int fig_count)
{
	t_tetr	*tetr;
	char	**repeat;

	tetr = (t_tetr *)(tetr_lst)->content;
	if (!placing(desk, desk_size, start, tetr))
		return (0);
	if (!(desk = insert_to_desk(desk, desk_size, start, tetr)))
		return (0);
	if (fig_count == 1)
		return (desk);
	else if (fig_count > 1 && (repeat = fillit(tetr_lst->next, desk, desk_size, create_marks(0), fig_count - 1)))
		return (repeat);
	else
	{
		delete_tetr_from_desk(desk, tetr);
		if (!next_position(desk, start, tetr, desk_size))
			return (0);
		return (fillit(tetr_lst, desk, desk_size, start, fig_count));
	}
}
