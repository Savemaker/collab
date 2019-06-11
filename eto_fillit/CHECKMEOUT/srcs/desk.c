/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:50:52 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/23 15:56:27 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fill.h"
#include "../libft/libft.h"

char	**draw_desk(int size)
{
	char	**desk;
	int		i;

	i = 0;
	if (!(desk = (char**)ft_memalloc(sizeof(*desk) * (size + 1))))
		stop();
	while (i < size)
	{
		if (!(desk[i] = ft_strnew((size_t)size)))
		{
			while (--i)
				ft_strdel(&desk[i]);
			free(desk);
			stop();
		}
		ft_memset(desk[i], '.', (size_t)size);
		i++;
	}
	return (desk);
}

void	print_desk(char **desk)
{
	int i;

	i = 0;
	while (desk[i] != '\0')
	{
		ft_putstr(desk[i]);
		ft_putchar('\n');
		i++;
	}
}

char	**insert_to_desk(char **desk, int desk_size, t_mark *start, t_tetr *tetr)
{
	int		row;
	int		col;
	char	**tetr_shape;

	row = 0;
	col = 0;
	tetr_shape = tetr->shape;
	while (tetr_shape[row] != NULL && row + start->row < desk_size && row < tetr->height)
	{
		col = 0;
		if ((start->col + tetr->width - col_brick_move(tetr)) <= desk_size)
		{
			while (tetr_shape[row][col] != '\0' && col < desk_size)
			{
				if (tetr_shape[row][col] != '.')
				{
					desk[row + start->row][col + start->col - col_brick_move(tetr)] = tetr_shape[row][col];
				}
				col++;
			}
		}
		else
			return (NULL);
		row++;
	}
	tetr->position->row = start->row;
	tetr->position->col = start->col - col_brick_move(tetr);
	return (desk);
}

void	delete_tetr_from_desk(char **desk, t_tetr *tetr)
{
	char	**shape;
	int		row;
	int		col;

	row = 0;
	shape = tetr->shape;
	while (shape[row] != NULL && row < tetr->height)
	{
		col = 0;
		while (shape[row][col] != '\0' && col < tetr->width)
		{
			if (shape[row][col] != '.')
			{
				desk[row + tetr->position->row][col + tetr->position->col] = '.';
			}
			col++;
		}
		row++;
	}
}

int		sizeof_desk(int fig_count, t_list *tetr_lst)
{
	int		i;
	t_tetr	*tetr;

	i = 2;
	tetr = (t_tetr *)(tetr_lst)->content;
	if (fig_count == 1)
	{
		if (tetr->width == 4 || tetr->height == 4)
			return (4);
		if (tetr->width == 3 || tetr->height == 3)
			return (3);
		if (tetr->width == 2 || tetr->height == 2)
			return (2);
	}
	while (i * i < fig_count * 4)
		i++;
	return (i);
}
