/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 17:38:26 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/11 17:38:32 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		processing(int argc, char **argv)
{
	uint16_t flags;
	uint16_t flags_quantity;

	flags = add_flags(argv, &flags_quantity);
	argv = check_dir(argc, argv, flags_quantity);
	print(make_argv_lst(argv, flags, &flags_quantity));
	return (1);
}

int		main(int argc, char **argv)
{
	if (!(processing(argc, argv)))
		exit(0);
	return (0);
}
