/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:44:41 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/06 15:15:26 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_list		*reading(const int fd)
{
	t_list	*list;
	t_list	*head;
	int		ret;
	char	buf[21];
	char	a;

	a = 'A';
	list = NULL;
	while ((ret = read(fd, buf, 21)) && ret != -1)
	{
		buf[ret] = '\0';
		head = createtr(buf, a++, ret);
		push_end(&list, head);
	}
	return (list);
}

// void	shapetoletter(char *buf, char a)
// {
// 	int i;

// 	i = 0;
// 	while (buf[i] != '\0')
// 	{
// 		if (buf[i] == '#')
// 			buf[i] = a;
// 		i++;
// 	}
// }


void		push_end(t_list **list, t_list *head)
{
	t_list *new;

	new = *list;
	if (new == NULL)
	{
		*list = head;
	}
	else	
	{
		while (new->next)
		{
			new = new ->next;
		}
		new -> next = head;
	}
}

void		ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
