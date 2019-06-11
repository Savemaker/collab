/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 17:45:39 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/03/24 18:11:49 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int	DidYouJustAssumeMySquare(t_list *list)
{
	t_list *head;
	t_tetr *a;
	int n;
	int i;

	i = 1;
	n = 0;
	if (!list)
		write(1, "oof\n", 4);
	head = list;
	a = head->content;
	while (head)
	{
		head = head->next;
		n++;
	}
	if ((n == 1) && (a->height == 2) && (a-> width== 2))
	{
		i = 2;
		return (i);
	}
	else if (n > 1)
	{
		n = n * 4;
		while (i <= n)
		{
			if (i * i >= n && i > 3)
				return (i);
			i++;
		}
	}
	else
	{
		return (4);
	}
	return (i);
}