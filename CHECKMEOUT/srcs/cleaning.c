/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:39:15 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/23 15:40:32 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fill.h"
#include "../libft/libft.h"

void		free_tetr_lst(t_tetr **tetr)
{
	int	residue;

	if (!tetr)
		return ;
	if ((*tetr)->shape)
	{
		residue = 0;
		while (residue < (*tetr)->height)
		{
			ft_strdel(&((*tetr)->shape[residue]));
			residue++;
		}
		free((*tetr)->shape);
	}
	free_mark(&((*tetr)->position));
	free(*tetr);
	*tetr = NULL;
}

void		clean_desk(char **desk, int desk_size)
{
	int i;

	i = 0;
	while (i < desk_size)
	{
		ft_strdel(&desk[i]);
		i++;
	}
}

void		free_mark(t_mark **mark)
{
	if (!mark)
		return ;
	free(*mark);
	*mark = NULL;
}

void		del_lst(t_list **begin_lst)
{
	t_list *current;
	t_list *next;
	t_tetr *present_tetr;

	current = *begin_lst;
	while (current != NULL)
	{
		present_tetr = current->content;
		free_tetr_lst(&present_tetr);
		next = current->next;
		free(current);
		current = next;
	}
	*begin_lst = NULL;
}
