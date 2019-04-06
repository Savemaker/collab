/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:03:43 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/06 17:09:15 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_list				*ft_lstnew(void const *content, size_t content_size)
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

t_list *createtr(char *buf, char a, int ret)
{
	t_list	*head;
	t_tetr	tetrimino;
	int i;

	tetrimino.height = 12;
	tetrimino.letter = a;
	tetrimino.shape = createshape(buf, a, ret);
	head = ft_lstnew(&tetrimino, sizeof(tetrimino));
	return (head);
}

char	**createshape(char *buf, char a, int ret)
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

void	trim(char **bufnew, char *buf, char a)
{
	char *new;
	int i;
	int j;
	int c;

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

void	freeshape(char **shape)
{
	int i;

	i = 0;
	while (i < 5)
		free(shape[i++]);
	free(shape);
}
void	deletelist(t_list **headref)
{
	t_list	*current; // deref headRef to get the real head
	t_list	*next;
	char	**shape;
	t_tetr	*a;
	int		i;

	i = 0;
	current = *headref;
	while (current != NULL)
	{
		a = current->content;
		shape = a ->shape;
		freeshape(shape);
		next = current->next; // note the next pointer
		free(a);
		free(current); // delete the node
		current = next; // advance to the next node
	}
	*headref = NULL; // Again, deref headRef to affect the real head back
}
