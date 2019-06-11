/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:59:50 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/23 16:40:22 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fill.h"
#include "../libft/libft.h"

t_list		*new_tetr(char *tetr_str, char letter)
{
	t_tetr	*tetr;
	t_list	*tetr_lst;

	if (!(tetr = create_tetr(tetr_str, letter)))
		stop();
	if (!(tetr_lst = ft_lstnew((void *)tetr, sizeof(*tetr))))
	{
		free_tetr_lst(&tetr);
		stop();
	}
	return (tetr_lst);
}

void	tetradd(t_list **beginlst, t_list **finallst, char *tetr_str, int fig_count)
{
	if (fig_count != 0 && ((*finallst)->next = new_tetr(tetr_str, (char)(65 + fig_count))))
		*finallst = (*finallst)->next;
	else if (fig_count == 0 && (*beginlst = new_tetr(tetr_str, (char)(65 + fig_count))))
		*finallst = *beginlst;
	else
	{
       del_lst(beginlst);
       stop();
	}
}
