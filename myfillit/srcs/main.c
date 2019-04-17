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
	char **board;


	t_tetr *tetr;
	char **sh;
	int i;
	i = 0;

	int b;
	int f;
	b = 0;
	f = 0;

	t_list *temp;


	sizedesk = 0;
	fd = open(argv[1], O_RDONLY);
	list = reading(fd);
	sizedesk = desksize(list);
	board = createboard(sizedesk);
	f = tryfillit(list, board, sizedesk);
	while (f == 1)
	{
		emptyboard(board, sizedesk);
		feedswapedlist(&list);                    //тут нужно подать пересортированный лист
		restorepos(list);
		f = tryfillit(list, board, sizedesk); // тут придумать значение для ф, которое при равенстве, запустить увелич борд
	}
//	while (b < sizedesk)
//	{
//		printf("%s\n", board[b++]);
//	}
	while (list)
	{
		i = 0;
		tetr = list->content;
		sh = tetr->shape;
		while (i < 4)
			printf("%s\n", sh[i++]);
		printf("\n");
		list = list->next;
	}
	return (0);
}

void	feedswapedlist(t_list **headref)
{
	t_list *head;
	t_list *temp;
	t_list *save;
	t_list *new;

	head = *headref;
	temp = head;
	
	head = head->next;
	save = head->next;
	head->next=temp;

	head = head->next;
	head->next = save;
}



//delete list and board
