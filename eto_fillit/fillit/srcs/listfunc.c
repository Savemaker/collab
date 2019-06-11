/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:44:59 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/03/24 18:11:33 by gbeqqo           ###   ########.fr       */
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

t_tetr		createtetr(char *buf, int ret, char a)
{
	t_tetr	new;
	char	**shape;
	char	**test;
	int		h;
	int		w;
	char	*newb;

	newb = ft_strndup(buf, ret);
	newb = trimbuf(newb, ret);
	h = valid_fig(newb) / 10;
	w = valid_fig(newb) % 10;
	newb = shapetoletter(newb, a);
	shape = create_shape(buf, a);
	new.height = h;
	new.width = w;
	new.shape = create_shape(newb, a);
	new.letter = a;
	return (new);
}

char		**create_shape(char *buff, char letter)
{
	char	**temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!(temp = (char**)malloc(sizeof(char *) * 5)))
		return (NULL);
	temp[4] = NULL;
	while (i < 4)
	{
		if (!(temp[i] = (char*)malloc(5)))
			return (NULL);
		j = 0;
		while (j < 4)
			temp[i][j++] = buff[k++];
		temp[i++][j] = '\0';
	}
	return (temp);
}
