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

	i = 0;
	fd = open("sample", O_RDONLY);
	list = reading(fd);
	temp = list;
	while (list)
	{
		tetr = list->content;
		a = tetr->shape;
		i = tetr ->width;
		printf("%d", i);
		// while (i < 4)
		// 	printf("\033[22;35m%s\n", a[i++]);
		printf("\n");
		list = list->next;
	}
	deletelist(&temp);
	return (0);
}
