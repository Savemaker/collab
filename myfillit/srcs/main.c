/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:30:54 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/07 00:35:59 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int main(void)
{
	int		fd;
	t_list	*list;
	t_list	*temp;
	t_tetr	*tetr;
	char	**a;
	int		i;
	int		sizedesk;
	char **board;


	i = 0;
	fd = open("sample", O_RDONLY);
	list = reading(fd);
//PRINT LISTS
//	while (list)
//	{
//		tetr = list -> content;
//		f = addtoboard(board, tetr, p, sizedesk);
//		i = 0;
//		while (i < 4)
//			printf("%s\n", a[i++]);
//		printf("\n");
//		list = list -> next;
//	}

//	while (list)
//	{
//		tetr = list -> content;
//		f = addtoboard(board, tetr, p, sizedesk);
//		if (f == 1)
//			p++;
//		else if (f == 0)
//			list = list -> next;
//		else if (list == NULL)
//			return (0);
//	}
		
//	while (i < sizedesk)
//		printf("%s\n", board[i++]);
//	deletelist(&temp);
	return (0);
}
