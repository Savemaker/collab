/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 17:24:38 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/03/27 17:48:58 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_list	*reading(const int fd)
{
	char	buf[21];
	t_list	*list;
	t_list	**tetr;
	t_tetr	tet;
	int		ret;
	char	a;

	tetr = &list;
	a = 'A';
	ret = 0;
	while ((ret = read(fd, buf, 21)) && (ret != -1))
	{
		buf[ret] = '\0';
		printf("%d", ret);
		tet = createtetr(buf, ret, a++);
		*tetr = ft_lstnew(&tet, sizeof(tet));
		tetr = &((*tetr)->next);
	}
	*tetr = NULL;
	return (list);
}
