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

int		sizeof_desk(t_list *list)
{
    t_list	*head;
    t_tetr	*tetr;
    int		n;
	
	n = 0;
	head = list;
	tetr = head->content;
	while (head)
	{
		head = head->next;
		n++;
	}
	if (tetr->height == 2 && tetr-> width== 2)
		return (2);
	else if (tetr->height == 4 || tetr->width == 4)
		return (4);
	else if (tetr->height == 3 || tetr->width == 3)
		return (3);
	else
		return (0);
}
