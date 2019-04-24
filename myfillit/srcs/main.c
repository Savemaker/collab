/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:30:54 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/24 18:44:16 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int main(int argc, char **argv)
{
	int		fd;
	t_list	*list;
	int		e;

	e = 0;
	fd = open(argv[1], O_RDONLY);
	list = reading(fd);
	e = solver(list);
	deletelist(&list);
	return (0);
}

int 	solver(t_list *list)
{
	char **desk;
	int size;

	size = desksize(list);
	desk = createboard(size);
	while (!(fillit(list, desk, size)))
	{
		emptyboard(desk, size);
		size+=1;
		if (!(desk = createboard(size)))
			return (0);
		restorepos(list);
	}
	int i;
	i = 0;
	while (i < size)
	{
		printf("%s\n", desk[i++]);
	}
	return (1);
}

int 	fillit(t_list *list, char **desk, int size)
{
	t_tetr *tetr;
	tetr = list->content;
	int a;
	while (list->pos < size * size)
	{
		a = adding(desk, size, list);
		if (a == 1)
			return (0);
		else
			{
				a = addtoboard(desk, size, tetr, list->pos);
				if (list->next != NULL)
				{
					a = fillit(list->next, desk, size);
					if (a == 0)
					{
						default_tet(desk, tetr->letter, size);
						list->pos += 1;
						list->next->pos = 0;
					}
					else
						return (1);
				}
				else
					return (1);
			}
	}
	return (0);
}

int			adding(char **board, int size, t_list *list)
{
	int a;
	t_tetr *tetr;

	tetr = list->content;
	a = 0;
	a = boardchecker(board, size, tetr, list->pos);
	if (a == 0)
		return (0);
	if (a == 1)
	{
		while (boardchecker(board, size, tetr, list->pos) == 1)
		{
			list->pos += 1;
			if (list->pos == size * size - 1)
				return (1);
		}
	}
	return (0);
}

size_t		factorial(size_t n)
{
	if (n == 0)
		return (1);
	return(n * factorial(n-1));
}


void	restorepos(t_list *list)
{
	while (list != NULL)
	{
		list->pos = 0;
		list = list ->next;
	}
}
