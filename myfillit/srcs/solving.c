/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:59:38 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/15 21:27:46 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		desksize(t_list *list)
{
	int i;
	t_tetr *tetr;
	i = 2;
	int fig_count;

	fig_count = 0;
	fig_count =listlen(list);

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
//	int i;
//	int n;
//	t_tetr *tetr;
//	t_list *temp;
//
//	i = 0;
//	n = 0;
//	temp = list;
//	while (list)
//	{
//		n++;
//		list = list -> next;
//	}
//	if (n == 1)
//	{
//		tetr = temp ->content;
//		if (tetr->height == 2 && tetr-> width == 2)
//			return (2);
//		else if (tetr->height == 4 || tetr->width == 4)
//			return (4);
//		else if (tetr->height == 3 || tetr->width == 3)
//			return (3);
//	}
//	else if (n > 1)
//	{
//		n = n * 4;
//		while (i < n)
//		{
//			if (i * i >= n && i > 3)
//				return (i);
//			i++;
//		}
//	}
//	return (0);
}

void	default_tet(char **board, char a, int size)
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
			if (board[i][j] == a)
				board[i][j] = '.';
			j++;
		}
		i++;
	}
}

int 	boardchecker(char **board, int size, t_tetr *tetr, int pos)
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

int 	addtoboard(char **board, int size, t_tetr *tetr, int pos)
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
				if (tetr->shape[y][x] == tetr->letter) {
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

//void	fillit(t_list *list, char **board, int size)
//{
//	int pos;
//	int i;
//	int f;
//	t_tetr *tetr;
//	char **shape;
//	int c;
//	t_list *back;
//
//	back = list;
//	tetr = NULL;
//	c = 0;
//	i = 0;
//	f = 0;
//	pos = 0;
//	i = 1;
//	while (i == 1)
//	{
//		c = 0;
//		i = addtoboard(board, size, list->content, pos);
//		tetr = list->content;
//		shape = tetr->shape;
//		while (shape[0][c++] == '.')
//			pos += 1;
//		if (i == 1)
//			pos++;
//		if (pos > (size * size) - 1)
//		{
//			pos = 0;
//			f = 1;
//			break ;
//		}
//	}
//	if (i == 2)
//	{
//		list->pos = pos;
//		list = list->next;
//		if (list != NULL)
//			fillit(list, board, size);
//	}
//	else if (f == 1)
//	{
//		list->pos = -1;
//	}
//}

//void	swap(t_list **head)
//{
//	t_list *cur;
//	t_list *temp;
//	t_list *list;
//
//	cur = *head;
//	temp = *head; //tut pervaya
//	list = *head;
//
//	cur = cur->next;
//	list = cur;
//	*head = list;
//	while (list->next != NULL)
//		list = list->next;
//	list->next = temp;
//	temp->next = NULL;
//}

int		checkpos(t_tetr *tetr)
{
	char **shape;

	shape = tetr->shape;
	if (shape[0][0] == '.')
		return (1); //emy pohuy na eto
	return (0);
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

//int		fc(t_tetr *tetr)
//{
//	char **shape;
//	int c;
//
//	c = 0;
//	shape = tetr->shape;
//	while (shape[0][c] == '.')
//		c++;
//	return (c);
//}



//void	slideleft(char **board, t_tetr *tetr, int size)
//{
//	int s;
//	int i;
//	int j;
//	char a;
//	char **shape;
//
//	a = tetr->letter;
//	shape = tetr->shape;
//	i = 0;
//	j = 0;
//	s = 0;
//	s = slidecheck(board, tetr, size);
//	if (s == 1)
//	{
//		while (i < size)
//		{
//			j = 0;
//			while (j < size)
//			{
//				if (board[i][j] == a)
//				{
//					board[i][j-1] = board[i][j];
//					board[i][j] = '.';
//				}
//				j++;
//			}
//			i++;
//		}
//	}
//}

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
//


//int		slidecheck(char **board, t_tetr *tetr, int size)
//{
//	int i;
//	int j;
//	int h;
//	int f;
//
//	f = 0;
//	h = 0;
//	i = 0;
//	j = 0;
//	while (i < size)
//	{
//		j = 0;
//		while (j < size)
//		{
//			if (board[i][j] == tetr->letter)
//			{
//				if (board[i][j-1] == '.')
//				{
//					f++;
//					j = size + 1;
//				}
//				if (f == tetr->height)
//					return (1);
//			}
//			j++;
//		}
//		i++;
//	}
//	return (0);
//}// int		addtoboard(char **board, t_tetr *tetr, int pos, int size) //t tetr?
//// {
//// 	int i;
//// 	int j;
//// 	int x;
//// 	int y;
//// 	char **shape;
//// 	int c;
////
//// 	c = 0;
//// 	y = 0;
//// 	x = 0;
//// 	shape = tetr->shape;
////
//// 	x = 0;
//// 	i = 0;
//// 	j = 0;
//// 	i = pos / size;
//// 	j = pos % size;
//// 	while (i < (tetr->height + i) && y < tetr->height)
//// 	{
//// 		j = pos % size;
//// 		x = 0;
//// 		while (j < (tetr->width + j) && x < tetr->width)
//// 		{
//// 				//c = fc(tetr);
//// 				if (pos % size + tetr->width - fc(tetr) > size)
//// 				{
//// 					default_tet(board, tetr->letter);
//// 					return (1);
//// 				}
//// 				else if (pos / size + tetr->height > size)
//// 				{
//// 					default_tet(board, tetr->letter);
//// 					return (1);
//// 				}
//// 				else if (board[i][j] != '.')
//// 				{
//// 					default_tet(board, tetr->letter);
//// 					return (1);
//// 				}
//// 			c = fc(tetr);
//// 			board[i][j] = shape[y][x];
//// 			j++;
//// 			x++;
//// 		}
//// 		i++;
//// 		y++;
//// 	}
//// 	while (slidecheck(board, tetr, size) == 1)
//// 		slideleft(board, tetr, size);
//// 	return (2);
//// }

// else if (shape[0][0] == '.')
// {
// 	i = pos / size;
// 	j = pos % size;
// 	x = 0;
// 	y = 0;
// 	while (shape[y][x] != tetr->letter)
// 		x++;
// 	while (i < tetr->height + i && y < tetr->height)
// 	{
// 		j = pos
// 	}
//int kostyl(t_tetr *tetr)
//{
//	if (tetr->height == 2 && tetr->width == 3)
//		return (1);
//	if (tetr->height == 3 && tetr->width == 2)
//		return (1);
//	return (0);
//}