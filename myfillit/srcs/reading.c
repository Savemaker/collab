/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:44:41 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/05 18:48:59 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_list		*reading(const int fd)
{
	t_list	*list;
	t_list	*head;
	int		ret;
	char	buf[21];
	char	a;

	a = 'A';
	list = NULL;
	while ((ret = read(fd, buf, 21)) && ret != -1)
	{
		buf[ret] = '\0';
		head = createtr(buf, a++, ret);
		push_end(&list, head);
	}
	return (list);
}

void		push_end(t_list **list, t_list *head)
{
	t_list *new;

	new = *list;
	if (new == NULL)
	{
		*list = head;
	}
	else	
	{
		while (new->next)
		{
			new = new ->next;
		}
		new -> next = head;
	}
}

t_list *createtr(char *buf, char a, int ret)
{
	t_list	*head;
	t_tetr	tetrimino;
	char	*newbuf;
	int i;

	newbuf = (char *)malloc(sizeof(char) * 16);
	ft_bzero(newbuf, 16);
	printf("%s", newbuf);
	tetrimino.height = 12;
	tetrimino.letter = a;
	tetrimino.shape = createshape(*buf, a);
	head = ft_lstnew(&tetrimino, sizeof(tetrimino));
	return (head);
}

char		**create_shape(char *buff, char letter)
{
	char	**temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!(temp = (char**)malloc(sizeof(char*) * 5)))
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



void	trimbuf(char *buf, char *newbuf, int ret)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (ret--)
	{
		if (buf[i] == '.')
			newbuf[c++] = '.';
		else if (buf[i] == '#')
			newbuf[c++] = '#';
		i++;
	}
	newbuf[16] = '\0';
}


void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * len);
	if (tmp == NULL)
		return (NULL);
	ft_memcpy(tmp, src, len);
	ft_memcpy(dst, tmp, len);
	free(tmp);
	return (dst);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void		*ft_memset(void *b, int c, size_t len)
{
	char	*p;

	p = (char *)b;
	while (len > 0)
	{
		p[len - 1] = c;
		len--;
	}
	return (b);
}

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



void	deletelist(t_list **headref)
{
	t_list	*current; // deref headRef to get the real head
	t_list	*next;
	t_tetr	*a;

	current = *headref;
	while (current != NULL)
	{
		a = current->content;
		next = current->next; // note the next pointer
		free(a);
		free(current); // delete the node
		current = next; // advance to the next node
	}
	*headref = NULL; // Again, deref headRef to affect the real head back
}

void		ft_memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}


	/*This function is designed to allocate and return a "fresh" zone of memory.
	 *The memory allocated is initialized to 0 using our ft_bzero function. If
	 the allocation fails we return NULL.*/

void		*ft_memalloc(size_t size)
{
	/*We first make a void variable of pointer m. This is so that we can use the
	 *zone of allocated memory that will be applied to it for any type of data.*/
	void	*m;
	/*We then use malloc to allocate memory to our m variable based on the size
	 *given in the parameter. If the allocation fails we return NULL. Otherwise
	 we then run the function ft_bzero on our allocated zone of memory m and
	 give it our size parameter. We then return our void variable m.*/
	m = malloc(size);
	if (m == NULL)
		return (NULL);
	ft_bzero(m, size);
	return (m);
}

void		ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
