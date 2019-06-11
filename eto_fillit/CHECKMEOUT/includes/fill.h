/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:43:59 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/23 16:46:36 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_H
# define FILL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct		s_mark
{
	int				row;
	int				col;
}					t_mark;

typedef	struct		s_tetr{
	int				height;
	int				width;
	char			**shape;
	t_mark			*position;
}					t_tetr;

void				stop(void);
void				valid_line(char *line, int *is_it_last_fig);
void				valid_fig(char *arr);
void				valid_fig_continue(char *arr);
void				stop(void);
void				open_file(char *filecontent);
t_list				*read_input(int fd);
void				check_count_of_tetr(int count);
void				valid_newlines(char *tetrline);
void				free_tetr_lst(t_tetr **tetr);
void				free_mark(t_mark **mark);
void				tetradd(t_list **beginlst, t_list **finallst, char *tetr_str, int fig_count);
char				**make_tetr_shape(int height, int width);
void				fill_tetr(char *shape, char letter, t_tetr *new);
t_tetr				*create_tetr(char *shape, char letter);
void				set_marks(char *shape, t_mark ***marks);
t_mark				*create_marks(int len);
int					solving(t_list *tetr);
void				print_desk(char **desk);
void				clean_desk(char **desk, int desk_size);
char				**fillit(t_list *tetr_lst, char **desk, int desk_size, t_mark *start, int fig_count);
void				del_lst(t_list **begin_lst);
char				**draw_desk(int size);
int					next_position(char **desk, t_mark *mark, t_tetr *tetr, int desk_size);
void				delete_tetr_from_desk(char **desk, t_tetr *tetr);
char				**insert_to_desk(char **desk, int desk_size, t_mark *start, t_tetr *tetr);
int					col_brick_move(t_tetr *tetr);
int					check_desk_opportunity(t_mark *start, t_tetr *tetr, int desk_size);
int					blank(char **desk, t_mark *start, t_tetr *tetr, int desk_size);
int					placing(char **desk, int desk_size, t_mark *start, t_tetr *tetr);
int					sizeof_desk(int fig_count, t_list *tetr_lst);

#endif
