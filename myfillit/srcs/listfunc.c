/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:03:43 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/22 15:32:23 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = malloc(content_size);
		if (new->content == NULL)
			return (NULL);
		ft_memmove(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}

int		listlen(t_list *list)
{
	int n;

	n = 0;
	while (list)
	{
		list = list->next;
		n++;
	}
	return (n);
}

t_list		*createtr(char *buf, char a, int ret)
{
	t_list	*head;
	t_tetr	tetrimino;
	int		i;
	int		t;
	int		c;

	c = 0;
	bufchecker(buf, a, ret);
	tetrimino.letter = a;
	tetrimino.shape = createshape(buf, a, ret);
	moveleft(tetrimino.shape, a);
	tetrimino.height = height(tetrimino.shape, a);
	moveup(tetrimino.shape, a, tetrimino.height);
	tetrimino.width = width(tetrimino.shape, a);
	val(&tetrimino);

	head = ft_lstnew(&tetrimino, sizeof(tetrimino));
	head->pos = 0;
	correctplace(head);
	head->content_size = 0;
	return (head);
}
void	moveleft(char **shape, char a)
{
	int i;
	int j;
	int move;
	char temp;

	i = 0;
	j = 0;
	move = 0;
	move = needtomove(shape, a);
	if (move == 0)
		return ;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (shape[i][j] == a)
			{
				shape[i][j-move] = shape[i][j];
				shape[i][j] = '.';
			}
			j++;
		}
		i++;
	}
}

int		needtomove(char **shape, char a)
{
	int i;
	int j;
	int n;
	int space;

	i = 0;
	j = 0;
	n = 0;
	space = 0;
	while (j < 4)
	{
		i = 0;
		n = 0;
		while (i < 4)
		{
			if (shape[i][j] == '.')
				n++;
			else if (shape[i][j] == a)
				return (space);
			i++;
		}
		if (n == 4)
			++space;
		j++;
	}
	return (space);
}

void	moveup(char **shape, char a, int h)
{
	int s;
	int i;
	int j;

	s = 0;
	i = 0;
	j = 0;
	s = checkmoveup(shape, a);
	if (s == 3)
	{
		ft_memcpy(shape[0], shape[3], 4);
		default_line(shape[3]);
	}
	else if (s == 2)
	{
		ft_memcpy(shape[0], shape[2], 4);
		ft_memcpy(shape[1], shape[3], 4);
		default_line(shape[2]);
		default_line(shape[3]);
	}
	else if (s == 1)
	{
		if (h == 1)
		{
			ft_memcpy(shape[0], shape[1], 4);
			default_line(shape[1]);
		}
		else if (h == 2)
		{
			ft_memcpy(shape[0], shape[1], 4);
			default_line(shape[1]);
			ft_memcpy(shape[1], shape[2], 4);
			default_line(shape[2]);
		}
		else if (h == 3)
		{
			ft_memcpy(shape[0], shape[1], 4);
			default_line(shape[1]);
			ft_memcpy(shape[1], shape[2], 4);
			default_line(shape[2]);
			ft_memcpy(shape[2], shape[3], 4);
			default_line(shape[3]);
		}
	}
}

void	default_line(char *line)
{
	int i;

	i = 0;
	while(line[i] != '\0')
	{
		line[i] = '.';
		i++;
	}
}

int		checkmoveup(char **shape, char a)
{
	int i;
	int j;
	int f;
	int space;

	space = 0;
	f = 0;
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		f = 0;
		while (j < 4)
		{
			if (shape[i][j] == '.')
				f++;
			else if (shape[i][j] == a)
				return (space);
			j++;
		}
		if (f == 4)
			++space;
		i++;
	}
	return (space);
}

char		**createshape(char *buf, char a, int ret)
{
	char	*newbuf;
	char	**shape;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	newbuf = (char *)malloc(sizeof(char) * 17);
	trim(&newbuf, buf, a);
	if (!(shape = (char**)malloc(sizeof(char *) * 5)))
		return (NULL);
	shape[4] = NULL;
	while (i < 4)
	{
		if (!(shape[i] = (char*)malloc(5)))
			return (NULL);
		j = 0;
		while (j < 4)
			shape[i][j++] = newbuf[k++];
		shape[i++][j] = '\0';
	}
	free(newbuf);
	return (shape);
}

void		trim(char **bufnew, char *buf, char a)
{
	char	*new;
	int		i;
	int		j;
	int		c;

	j = 0;
	i = 0;
	c = 0;
	new = *bufnew;
	while (j < 16)
	{
		if (buf[c] == '#')
		{
			new[i++] = a;
			j++;
		}
		else if (buf[c] == '.')
		{
			new[i++] = '.';
			j++;
		}
		c++;
	}
	new[i] = '\0';
}

void		deletelist(t_list **headref)
{
	t_list	*current;
	t_list	*next;
	char	**shape;
	t_tetr	*a;
	int		i;

	i = 0;
	current = *headref;
	while (current != NULL)
	{
		a = current->content;
		shape = a->shape;
		freeshape(shape);
		next = current->next;
		free(a);
		free(current);
		current = next;
	}
	*headref = NULL;
}
