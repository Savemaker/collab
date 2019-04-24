/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:48:41 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/07 00:48:15 by gbeqqo           ###   ########.fr       */
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
				break ;
			}
			j++;
		}
		i++;
	}
	return (h);
}

int		width(char **shape, char a)
{
	int i;
	int j;
	int c;
	int t;
	
	t = 0;
	c = 0;
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (shape[i][j] == a)
				c = j + 1;
			j++;
		}
		if (c >= t)
			t = c;
		i++;
	}
	return (t);
}

int		touch(char **shape, char a)
{
	int i;
	int j;
	int t;
	int y;

	y = 0;
	i = 0;
	j = 0;
	t = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			y = count(shape, &i, &j ,a);
			t = y + t;
			j++;
		}
		i++;
	}
	return (t);
}


void	stop(void)
{
	write(1, "error\n", 6);
	exit(0);
}

int		count(char **shape, int *y, int *x, char a)
{
	int t;
	int i;
	int j;

	i = *y;
	j = *x;
	t = 0;
	if (shape[i][j] == a)
	{
		if (i == 3)
		{
			if (shape[i - 1][j] == a)
				t += 1;
			if (shape[i][j+1] == a)
				t += 1;
			if (j > 0 && shape[i][j - 1] == a)
				t += 1;
		}
		else
			{	
				if (shape[i][j +1] == a)
						t +=1;
				if (j > 0 && shape[i][j - 1] == a)
						t+=1;
				if (i > 0 && shape[i-1][j] == a)
						t += 1;
				if (shape[i + 1][j] == a)
						t+=1;
			}
	}
	return (t);
}

int		quantity(char **shape, char a)
{
	int i;
	int	j;
	int c;

	i = 0;
	j = 0;
	c = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (shape[i][j] == a)
				c++;
			j++;
		}
		i++;
	}
	return (c);
}

void		val(t_tetr *tetr)
{
	int t;
	int q;

	t = 0;
	q = 0;
	t = touch(tetr->shape, tetr->letter);
	q = quantity(tetr->shape, tetr->letter);
	if (q == 4 && t == 8)
	{
		if (tetr->height != 2 && tetr->height != 2)
			stop();
	}
	else if (q == 4 && t != 6)
		stop();
}
