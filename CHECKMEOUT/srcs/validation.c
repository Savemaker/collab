/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:25:56 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/23 16:29:55 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fill.h"
#include "../libft/libft.h"

void	valid_line(char *line, int *is_it_last_fig)
{
	int len;
	int brick;
	int str_count;

	brick = 0;
	len = 0;
	while (line[len])
	{
		str_count = len / 5;
		if ((len + 1 % 5 == 0 && line[len] != '\n') || (line[len] != '.' && line[len] != '#' && line[len] != '\n'))
			stop();
		if ((len + 1) % 5 != 0 && str_count < 4 && ((line[len] != '.' && line[len] != '#')))
			stop();
		if (line[len] == '#')
			brick++;
		len++;
	}
	str_count = len / 5;
	if (line[20] == '\0')
		*is_it_last_fig = 1;
	if (!brick || brick != 4 || str_count != 4)
		stop();
}

void	valid_newlines(char *tetrline)
{
	int i;

	i = 19;
	while (i > 0)
	{
		if (tetrline[i] != '\n')
			stop();
		i = i - 5;
	}
	if (tetrline[20] != '\n' && tetrline[20] != '\0')
		stop();
}

void	valid_fig_continue(char *tetrstr)
{
	if (*(tetrstr + 1) == '#' && *(tetrstr + 2) == '#' && *(tetrstr + 7) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 11) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 4) == '#' && *(tetrstr + 5) == '#')
		;
	else if (*(tetrstr + 4) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 9) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 7) == '#')
		;
	else if (*(tetrstr + 4) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 6) == '#')
		;
	else if (*(tetrstr + 4) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 10) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 10) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 2) == '#' && *(tetrstr + 6) == '#')
		;
	else
		stop();
}

void	valid_fig(char *tetrstr)
{
	while (*tetrstr != '#')
		tetrstr++;
	if (*(tetrstr + 5) == '#' && *(tetrstr + 10) == '#' && *(tetrstr + 15) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 2) == '#' && *(tetrstr + 3) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 6) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 10) == '#' && *(tetrstr + 11) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 11) == '#')
		;
	else if (*(tetrstr + 2) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 11) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 2) == '#' && *(tetrstr + 5) == '#')
		;
	else if (*(tetrstr + 3) == '#' && *(tetrstr + 4) == '#' && *(tetrstr + 5) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 10) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 9) == '#' && *(tetrstr + 10) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 7) == '#')
		;
	else
		valid_fig_continue(tetrstr);
}
