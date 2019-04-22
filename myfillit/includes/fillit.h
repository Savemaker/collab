/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:31:09 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/22 15:32:36 by gbeqqo           ###   ########.fr       */
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
	int				pos;
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
int					height(char **shape, char a);
int					width(char **shape, char a);
int					touch(char **shape, char a);
int					count(char **shape, int *i, int *j, char a);
int					quantity(char **shape, char a);
void				val(t_tetr *tetr);
void				stop(void);
void				bufchecker(char *buf, char a, int ret);
void				nchecker(char *buf, int ret);
int					desksize(t_list *list);
char				**createboard(int s);
int					checkmoveup(char **shape, char a);
void				default_line(char *line);
void				moveup(char **shape, char a, int h);
int					needtomove(char **shape, char a);
void				moveleft(char **shape, char a);
int					pathfinder(char **shape, int l, char a);
void				default_tet(char **board, char a);
int					addtoboard(char **board, int size, t_tetr *tetr, int pos);
int					recursion(t_list *list, char **board, int size, int pos);
int					tryfillit(t_list *list, char **board, int size);
int					slidecheck(char **board, t_tetr *tetr, int size);
void				slideleft(char **board, t_tetr *tetr, int size);
int					listlen(t_list *list);
int					fc(t_tetr *tetr);
void				freeboard(char **board, int size);
int 				boardchecker(char **board, int size, t_tetr *tetr, int pos);
void				switcheer(t_list **list);
void				emptyboard(char **board, int size);
int					checkpos(t_tetr *tetr);
void				swap(t_list **a, t_list **b);
void				swap_swag(t_list **list);
int					checklist(t_list *list);
void				correctplace(t_list *list);
void				restorepos(t_list *list);
size_t				factorial(size_t n);
size_t				lenrec(t_list *list);
int					fillit(t_list *list, char **board, int sizedesk);

#endif
