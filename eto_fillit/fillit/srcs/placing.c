/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 19:28:42 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/03/24 18:11:42 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"
#include <stdio.h>

// задача сделать доску и добавить сюда тетримины, которым изначально будет норм

char **insert_to_board(char **board, t_list *list) //весьма наивно, но добавляет фигуры на доску
{
	char **shape;
	t_tetr *tetr;
	char letter;
	t_list *node;
	int h;
	int w;
	int i = 0;
	int j = 0;

	if (!list)
	{
		printf("oops");
	}
	node = list;
	while (node)
	{
		j = 0;
		i = 0;
		tetr = node ->content;
		h = tetr ->height;
		shape = tetr->shape;
		letter = tetr ->letter;
		while (i < 4)
		{	
			j = 0;
			while (j < 4)
			{
				if (shape[i][j] == letter)
				{
					board[i][j] = shape[i][j];
					j++;
				}
				else	
					break;
			}
			i++;
		}
		node = node ->next;
	}

	return (board);
}

// char **holla(char **board, t_list *list)
// {
// 	t_list *head;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	head = list;
// 	while (head)
// 	{
		
// 	}	
// }

// int		vaccant(char **board, t_list *list)
// {
// 	t_list *head;
// 	t_tetr *tetr;
// 	char **shape;
// 	int h;
// 	int w;

// 	head = list;
// 	tetr = head ->content;
// 	shape = tetr ->shape;
// 	h = 0;
// 	w = 0;
// 	h = tetr->height;
// 	w = tetr->shape;
// }

char	**create_board(int row)
{
	char	**board;
	char	*arr;
	int		i;

	i = 0;
	arr = (char *)malloc(sizeof(char) * row * row + 1);
	arr[row * row + 1] = '\0';
	board = (char **)malloc(sizeof(char) * row);
	while (i < row)
	{
		board[i] = &(arr[i * row]);
		i++;
	}
	return (board);
}

void	init_board(char **board, int row, char s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < row)
	{
		j = 0;
		while (j < row)
		{
			board[i][j] = s;
			j++;
		}
		i++;
	}
}

void	printboard(char **board, int row)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < row)
	{
		j = 0;
		while (j < row)
		{
			write(1, &board[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
