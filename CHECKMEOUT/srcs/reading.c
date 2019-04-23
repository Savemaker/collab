/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:04:52 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/23 16:30:27 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fill.h"
#include "../libft/libft.h"

void		check_count_of_tetr(int count)
{
	if (count > 26 || count < 0)
	{
		ft_putstr("Too much tetromino");
		stop();
	}
}

void		open_file(char *filecontent)
{
	t_list	*tetr;
	int		fd;

	if ((fd = open(filecontent, O_RDONLY)) == 1)
		stop();
	if (!(tetr = read_input(fd)))
	{
		close(fd);
		stop();
	}
	if (!solving(tetr))
		stop();
}

t_list		*read_input(int fd)
{
	char	*tetrline;
	int		fig_count;
	t_list	*finalst;
	t_list	*beginlst;
	int		is_it_last_fig;

	is_it_last_fig = 0;
	tetrline = ft_strnew(21);
	fig_count = 0;
	while (read(fd, tetrline, 21))
	{
		check_count_of_tetr(fig_count + 1);
		valid_newlines(tetrline);
		valid_line(tetrline, &is_it_last_fig);
		//tetrline[20] = '\0;
		tetradd(&beginlst, &finalst, tetrline, fig_count);
		ft_bzero(tetrline, 21);
		fig_count++;
	}
	ft_strdel(&tetrline);
	if ((fig_count == 0) || !(is_it_last_fig))
		stop();
	beginlst->content_size = (size_t)fig_count;
	return (beginlst);
}
