/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:59:38 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/06 20:28:50 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		desksize(t_list *list)
{
	int i;
	int n;
	t_tetr *tetr;
	t_list *temp;

	i = 0;
	n = 0;
	temp = list;
	while (list)
	{
		n++;
		list = list -> next;
	}
	if (n == 1)
	{
		tetr = temp ->content;
		if (tetr->height == 2 && tetr-> width == 2)
			return (2);
		else if (tetr->height == 4 || tetr->width == 4)
			return (4);
		else if (tetr->height == 3 || tetr->width == 3)
			return (3);
	}
	else if (n > 1)
	{
		n = n * 4;
		while (i < n)
		{
			if (i * i >= n && i > 3)
				return (i);
			i++;
		}
	}
	return (0);
}

void	default_tet(char **board, char a)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (board[i][j] == a)
				board[i][j] = '.';
			j++;
		}
		i++;
	}
}

int		addtoboard(char **board, t_tetr *list, int pos, int size) //t tetr?
{
	int i;
	int j;
	int x;
	int y;
	char **shape;

	if (list == NULL)
		return (12);
	y = 0;
	x = 0;
	shape = tetr->shape;
	i = 0;
	j = 0;
	i = pos / size;
	j = pos % size;
	while (i < (tetr->height + i) && y < tetr->height)
	{
		j = pos % size;
		x = 0;
		while (j < (tetr->width + j) && x < tetr->width)
		{
			if (pos % size + tetr->width > size)
			{
				default_tet(board, tetr->letter);
				return (1);
			}
			else if (pos / size + tetr->height > size)
			{
				default_tet(board, tetr->letter);
				return (1);
			}
			else if (board[i][j] != '.')
			{
				default_tet(board, tetr->letter);
				return (1);
			}
				
			board[i][j] = shape[y][x];
			j++;
			x++;
		}
		i++;
		y++;
	}
	return (2);
}

//int		fillit(t_list *list, int size, int board)
//{
//	t_list *li;
//	int res;
//	static int p;
//	int flag;
//	int c;
//	t_tetr *tet;
//
//	li = list;
//	flag = 0;
//	p = 0;
//	res = 0;
//	c = 0;
//	if (res == 2)
//	{
//		li->pos = p;
//		c++;
//		li = li->next;
//		flag = 0;
//	}
//	else if (res == 1)
//	{
//		p++;
//		if (p > (size * size - 1))
//			flag = 1;
//		if (flag == 1)
//		{
//			while (l < (c-1))
//				li = list->next;
//			c -= 1;
//			tet = li -> content;
//			default_tet(board, tet->letter);
//			p = li->pos + 1;
//		}
//	}
//}