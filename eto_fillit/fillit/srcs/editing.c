/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:07:48 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/03/24 18:11:27 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

char	*trimbuf(char *newbuf, int ret)
{
	char	*res;
	int		i;
	int		c;

	i = 0;
	c = 0;
	res = (char *)malloc(sizeof(char) * 16);
	while (ret--)
	{
		if (newbuf[i] == '.')
			res[c++] = '.';
		else if (newbuf[i] == '#')
			res[c++] = '#';
		i++;
	}
	res[16] = '\0';
	return (res);
}

char	*shapetoletter(char *buf, char a)
{
	int i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '#')
			buf[i] = a;
		i++;
	}
	return (buf);
}

// char **mooooveBitch(t_tetr *tetr, int ass)
// {
// 	int i;
// 	int j;
// 	t_tetr *head;
// 	char **shape;
// 	int c;

	
// }
