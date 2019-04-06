/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:31:09 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/06 16:57:28 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdio.h> //alouberipotomokbby
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_list{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_tetr{
	int				height;
	int				width;
	char			letter;
	char			**shape;
}					t_tetr;

t_list				*reading(const int fd);
t_list				*createtr(char *buf, char a, int ret);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				deletelist(t_list **headref);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				push_end(t_list **list, t_list *head);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_strncpy(char *dst, const char *src, size_t n);
int					ft_strlen(const char *s);
char				**createshape(char *buf, char a, int ret);
void				trim(char **bufnew, char *buf, char a);
void				freeshape(char **shape);

#endif
