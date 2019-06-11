/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:43:05 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/03/24 18:11:36 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"
#include <stdio.h>

int	main(void)
{
	int fd;
	t_list *list;
	t_tetr *a;
	char **shap;
	char **board;
	int h;
	int w;
	int i;
	int calc = 0; //  эта вещб (функция) будет вычислять нужную высоту (и ширину) квадрата

	i = 0;
	fd = open("sample", O_RDONLY);
	list = reading(fd);
	calc = DidYouJustAssumeMySquare(list);
	// list = list -> next;
	// list = list -> next;
	a = list ->content;
	shap = a ->shape;
	h = a ->height;
	w = a -> width;
	printf("height = %d\n", h);
	printf("width = %d\n", w);
	// while (i < 4)
	// {
	// 	printf("%s\n", shap[i]);
	// 	i++;
	// }
	board = create_board(calc);
	init_board(board, calc, '.');
	//board = insert_to_board(board, list);
	printboard(board, calc);
	return (0);
}
