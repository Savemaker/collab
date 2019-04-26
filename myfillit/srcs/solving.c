/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:59:38 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/26 17:40:09 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		desksize(t_list *list)
{
	int		i;
	t_tetr	*tetr;
	int		fig_count;

	i = 2;
	fig_count = 0;
	fig_count = listlen(list);
	tetr = list->content;
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

void	default_tet(char **board, t_list *list, int size)
{
	int i;
	int j;
	t_tetr *tetr;

	tetr = list->content;
	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (board[i][j] == tetr->letter)
				board[i][j] = '.';
			j++;
		}
		i++;
	}
}

int		boardchecker(char **board, int size, t_tetr *tetr, int pos)
{
	int i;
	int j;
	int x;
	int y;
	int c;

	c = 0;
	i = 0;
	j = 0;
	x = 0;
	y = 0;
	i = pos / size;
	j = pos % size;
	while (i < size && y < tetr->height)
	{
		j = pos % size;
		while (j < size && x < tetr->width)
		{
			if (board[i][j] == '.' && tetr->shape[y][x] == tetr->letter)
			{
				c++;
			}
			j++;
			x++;
			if (x > tetr->width && c == 4)
				return (0);
			if (x > tetr->width && c != 4)
				return (1);
		}
		i++;
		y++;
		x = 0;
	}
	if (c == 4)
		return (0);
	return (1);
}

int		addtoboard(char **board, int size, t_tetr *tetr, int pos)
{
	int i;
	int j;
	int x;
	int y;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	i = pos / size;
	if (!(boardchecker(board, size, tetr, pos)))
	{
		while (i < size && y < tetr->height)
		{
			j = pos % size;
			while (j < size && x < tetr->width)
			{
				if (tetr->shape[y][x] == tetr->letter)
				{
					board[i][j] = tetr->shape[y][x];
				}
				j++;
				x++;
				if (x > tetr->width)
					return (1);
			}
			i++;
			y++;
			x = 0;
		}
		return (0);
	}
	return (1);
}

void	emptyboard(char **board, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			board[i][j] = '.';
			j++;
		}
		i++;
	}
}
