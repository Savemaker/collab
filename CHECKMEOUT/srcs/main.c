/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:03:10 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/23 16:03:43 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fill.h"
#include "../libft/libft.h"

void	stop(void)
{
	ft_putstr("error\n");
	exit(0);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		open_file(argv[1]);
	}
	else
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" [input_file]\n");
		return (1);
	}
	return (0);
}
