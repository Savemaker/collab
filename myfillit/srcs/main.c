/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:30:54 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/05 18:49:41 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int main()
{
	int fd;
	t_list *list;
	t_tetr *tetr;
	char **a;

	fd = open("sample", O_RDONLY);
	list = reading(fd);
	deletelist(&list);	
	return (0);
}