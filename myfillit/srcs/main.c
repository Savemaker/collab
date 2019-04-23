/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:30:54 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/16 14:39:37 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int main(int argc, char **argv)
{
	int fd;
	t_list *list;
	int sizedesk;
	t_tetr *tetr;
	t_list *temp;

	fd = open(argv[1], O_RDONLY);
	list = reading(fd);
	tetr = list->content;
	temp = list;
	//temp->content_size = 1;
	int e;
	e = 0;
	e = solver(list);
//	//e = addtoboard(board, sizedesk, list->content, list->pos);
//	int a;
//	a = 0;
//	a = adding(board, sizedesk, list->content, 0);
//	list = list->next;
//	a = adding(board, sizedesk, list->content, 0);
//	e = 0;
//	while (e < sizedesk)
//	{
//		printf("%s\n", board[e++]);
//	}
	return (0);
}

void	check(t_list *list)
{
	t_tetr *tetr;

	tetr = list->content;
}

int 	solver(t_list *list)
{
	char **desk;
	int size;
	//t_list *temp;

	//temp = list
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
//				int s;
//
//				s = 0;
//				while (s < size) {
//					printf("%s\n", desk[s++]);
//				}
//				printf("\n");
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


//char **fillit(t_list *list, char **desk, int size, int fig, int pos)
//{
//	t_tetr *tetr;
//	int a;
//	char **repeat;
//
//	tetr = list->content;
//	a = 0;
//	pos = adding(desk, size, list);
//	list->pos = pos;
//	a = addtoboard(desk, size, tetr, list->pos);
////	int s;
////	s = 0;
////	while (s < size)
////		printf("%s\n", desk[s++]);
//	if (a == 1)
//		return (0);
//	if (fig == 1)
//		return (desk);
//	else if (fig > 1 && (repeat = fillit(list->next, desk, size, fig -1, list->pos)))
//		return (repeat);
//	else
//	{
//		default_tet(desk, tetr->letter);
//		list->pos += 1;
//		a = adding(desk, size, list);
//		if (a == 1)
//		{
//			list->pos = 0;
//			return (0);
//		}
//		return (fillit(list, desk, size, fig, a));
//	}
//}

int			addtoboard(char **board, int size, t_tetr *tetr, int pos);

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

//int		fillit(t_list *list, char **board, int sizedesk)
//{
//	int f;
//	int c;
//	int n;
//	int b;
//
//	b = 0;
//	c = 0;
//	n = 0;
//	f = 0;
//	f = tryfillit(list, board, sizedesk);
//	c++;
//	n = lenrec(list);
//	b = factorial(n);
//	while (f == 1)
//	{
//		emptyboard(board, sizedesk);
//		restorepos(list);
//		swap_swag(&list);
//		f = tryfillit(list, board, sizedesk);
//		c++;
//		if (c > b)
//		{
//			f = 2;
//			break;
//		}
//	}
//	return (f);
//}


size_t		factorial(size_t n)
{
	if (n == 0)
		return (1);
	return(n * factorial(n-1));
}

size_t lenrec(t_list *list)
{
	size_t n;
	
	n = 0;
	while (list)
	{
		n++;
		list = list->next;
	}
	return (n);
}
void	swap_swag(t_list **list)
{
	t_list *head;
	t_list *cur;
	t_list *temp;
	
	head = *list;
	cur = head;
	temp = head;
	
	while (cur->content_size != 1)
		cur = cur->next;
	if (cur->next != NULL)
		swap(&cur, &cur->next);
	if (cur->next == NULL)
	{
		temp->content_size = 0;
		cur->content_size = 1;
		swap(&cur, &temp);
	}
}

void	swap(t_list **a, t_list **b)
{
	t_list *temp;
	t_list *f;
	t_list *s;
	
	f = *a;
	s = *b;
	temp = (t_list *)malloc(sizeof(f));
	temp->content = f->content;
	temp->content_size = f->content_size;
	temp->pos = f->pos;
	f->content = s->content;
	f->content_size = s->content_size;
	f->pos = s->pos;
	s->content = temp->content;
	s->content_size = temp->content_size;
	s->pos = temp->pos;
	//freetemppls
}

int tryfillit(t_list *list, char **board, int size)
{
	int i;
	int p;
	int f;

	f = 0;
	i = 0;
	p = 0;

	i = addtoboard(board, size, list->content, list->pos);
	while (i == 2)
	{

		list = list->next;
		if (list == NULL)
			break;
		i = addtoboard(board, size, list->content, list->pos);
		while (i == 1)
		{
			list->pos++;
			if (list->pos > (size * size) - 1) {
				f = 1;
				break;
			}
			i = addtoboard(board, size, list->content, list->pos);
		}
	}
	return (f);
}

void	restorepos(t_list *list)
{
	while (list != NULL)
	{
		list->pos = 0;
		list = list ->next;
	}
}

void	correctplace(t_list *list)
{
	char **shape;
	t_tetr *tetr;
	int i;
	int j;

	tetr = list->content;
	shape = tetr->shape;
	i = 0;
	j = 0;
	while (shape[0][j] == '.' && j < 4)
		j++;
	list->pos = list->pos + j;
}

//while (list)
//	{
//		i = 0;
//		tetr = list->content;
//		sh = tetr->shape;
//		while (i < 4)
//			printf("%s\n", sh[i++]);
//		printf("\n");
//		list = list->next;
//	}



//delete list and board
int checklist(t_list *list)
{
	t_list *head;

	head = list;
	while (head != NULL)
	{
		if (head->pos == -1)
			return (-1);
		head = head -> next;
	}
	return (0);
}