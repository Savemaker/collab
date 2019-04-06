/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:48:41 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/06 23:54:03 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		height(char **shape, char a)
{
	int i;
	int j;
	int h;

	i = 0;
	h = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (shape[i][j] == a)
			{
				h++;
				j++;
				break;
			}
			j++;
		}
		i++;
	}
	return (h);
}