/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 17:49:31 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/03/24 18:11:57 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

void	stop(void)
{
	write(1, "katyazaimi50k\n", 14);
	exit(0);
}

int		valid_fig_continue(char *arr)
{
	if (*(arr + 1) == '#' && *(arr + 2) == '#' && *(arr + 4) == '#')
		return (23);
	else if (*(arr + 2) == '#' && *(arr + 3) == '#' && *(arr + 4) == '#')
		return (23);
	else if (*(arr + 1) == '#' && *(arr + 2) == '#' && *(arr + 6) == '#')
		return (23);
	else if (*(arr + 4) == '#' && *(arr + 5) == '#' && *(arr + 6) == '#')
		return (23);
	else if (*(arr + 3) == '#' && *(arr + 4) == '#' && *(arr + 5) == '#')
		return (23);
	else if (*(arr + 1) == '#' && *(arr + 2) == '#' && *(arr + 5) == '#')
		return (23);
	else if (*(arr + 1) == '#' && *(arr + 3) == '#' && *(arr + 4) == '#')
		return (23);
	else if (*(arr + 1) == '#' && *(arr + 5) == '#' && *(arr + 6) == '#')
		return (23);
	else
		stop();
	return (23);
}

int		valid_fig(char *arr)
{
	while (*arr != '#')
		arr++;
	if (*(arr + 4) == '#' && *(arr + 8) == '#' && *(arr + 12) == '#')
		return (41);
	else if (*(arr + 1) == '#' && *(arr + 2) == '#' && *(arr + 3) == '#')
		return (14);
	else if (*(arr + 4) == '#' && *(arr + 8) == '#' && *(arr + 9) == '#')
		return (32);
	else if (*(arr + 1) == '#' && *(arr + 5) == '#' && *(arr + 9) == '#')
		return (32);
	else if (*(arr + 1) == '#' && *(arr + 4) == '#' && *(arr + 8) == '#')
		return (32);
	else if (*(arr + 4) == '#' && *(arr + 7) == '#' && *(arr + 8) == '#')
		return (32);
	else if (*(arr + 4) == '#' && *(arr + 5) == '#' && *(arr + 9) == '#')
		return (32);
	else if (*(arr + 3) == '#' && *(arr + 4) == '#' && *(arr + 7) == '#')
		return (32);
	else if (*(arr + 3) == '#' && *(arr + 4) == '#' && *(arr + 8) == '#')
		return (32);
	else if (*(arr + 4) == '#' && *(arr + 5) == '#' && *(arr + 8) == '#')
		return (32);
	else if (*(arr + 1) == '#' && *(arr + 4) == '#' && *(arr + 5) == '#')
		return (22);
	else
		valid_fig_continue(arr);
	return (23);
}
