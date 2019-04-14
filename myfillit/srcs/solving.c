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

int kostyl(t_tetr *tetr)
{
	if (tetr->height == 2 && tetr->width == 3)
		return (1);
	if (tetr->height == 3 && tetr->width == 2)
		return (1);
	return (0);
}

int		addtoboard(char **board, t_tetr *tetr, int pos, int size) //t tetr?
{
	int i;
	int j;
	int x;
	int y;
	char **shape;

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
	while (slidecheck(board, tetr) == 1)
		slideleft(board, tetr);
	return (2);
}

int		slidecheck(char **board, t_tetr *tetr)
{
	int i;
	int j;
	int h;
	int f;

	f = 0;
	h = 0;
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (board[i][j] == tetr->letter)
			{
				if (board[i][j-1] == '.')
				{
					f++;
					j = 4;
				}
				if (f == tetr->height)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	slideleft(char **board, t_tetr *tetr)
{
	int s;
	int i;
	int j;
	char a;
	char **shape;

	a = tetr->letter;
	shape = tetr->shape;
	i = 0;
	j = 0;
	s = 0;
	s = slidecheck(board, tetr);
	if (s == 1)
	{
		while (i < 4)
		{
			j = 0;
			while (j < 4)
			{
				if (board[i][j] == a)
				{
					board[i][j-1] = board[i][j];
					board[i][j] = '.';
				}
				j++;
			}
			i++;
		}
	}
}

void	fillit(t_list *list, char **board, int size)
{
	int pos;
	int i;
	int f;
	t_list *back;

	f = 0;
	pos = list->pos;
	i = 1;
	while (i == 1)
	{
		i = addtoboard(board, list->content, pos, size);
		pos++;
		if (pos > (size * size) - 1)
		{
			pos = 0;
			f = 1;
			break ;
		}
	}
	if (i == 2)
	{
		list->pos = pos;
		back = list;
		list = list->next;
		if (list != NULL)
			fillit(list, board, size);
	}
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