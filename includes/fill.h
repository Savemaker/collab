
#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>


#include "../libft/libft.h"

typedef struct	s_mark
{
	int			row;
	int			col;
}				t_mark;

typedef	struct		s_tetr{
	int				height;
	int				width;
	char			**shape;
	t_mark			*position;
}					t_tetr;



//typedef struct		s_list{
//	void			*content;
//	size_t			content_size;
//	struct s_list	*next;
//
//}					t_list;

void stop(void);
void valid_line(int fd,char *line);
void valid_fig(char *arr);
void valid_fig_continue(char *arr);
void stop(void);
void open_file(char *fileContent);
t_list	*read_input(int fd);
void				check_count_of_tetr(int count);
void		valid_newlines(char *tetrLine);
void		free_tetr_lst(t_tetr **tetr);
void		free_mark(t_mark **mark);
void	tetradd(t_list **beginLst, t_list **finalLst, char *tetr_str, int fig_count);


void	del_tetr(void *content, size_t content_size);


char		**make_tetr_shape(int height, int width);
void	fill_tetr(char *shape, char letter, t_tetr *new);
t_tetr		*create_tetr(char *shape, char letter);
void set_marks(char *shape, t_mark ***marks);
t_mark		*create_marks(int len);
void solving(t_list **tetr);
void print_desk(char **desk);
void clean_desk(char **desk, int desk_size);
int fillit(char **desk, t_mark *start, t_list **finish);
#endif
