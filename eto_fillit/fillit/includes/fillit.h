/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:00:54 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/03/24 17:25:32 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef	struct		s_tetr{
	int				height;
	int				width;
	char			letter;
	char			**shape;
}					t_tetr;

typedef struct		s_list{
	void			*content;
	size_t			content_size;
	struct s_list	*next;

}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				*ft_memmove(void *dst, const void *src, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strndup(const char *s, size_t n);
t_list				*reading(const int fd);
t_tetr				createtetr(char *buf, int ret, char a);
char				*trimbuf(char *newbuf, int ret);
char				*shapetoletter(char *buf, char a);
int					ft_strlen(const char *s);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				**create_shape(char *buff, char letter);
void				stop(void);
int					valid_fig_continue(char *arr);
int					valid_fig(char *arr);
char				**create_board(int row);
char				**insert_to_board(char **board, t_list *list);
void				init_board(char **board, int row, char s);
void				printboard(char **board, int row);
int					DidYouJustAssumeMySquare(t_list *list);

#endif
