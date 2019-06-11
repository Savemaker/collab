#include "../includes/fill.h"
#include "../libft/libft.h"

t_tetr		*create_tetr(char *shape, char letter)
{
	t_tetr *new_tetr;
	t_mark **marks;

	if (!shape)
		stop();
	if (!(marks = (t_mark **)ft_memalloc(sizeof(*marks) * 2)))
		stop();
	valid_fig(shape);
	if ((new_tetr = (t_tetr *)ft_memalloc(sizeof(*new_tetr))))
	{
		set_marks(shape, &marks);
		new_tetr->position = marks[0];
		new_tetr->height = ((marks[1])->row - (marks[0])->row) + 1;
		new_tetr->width = ((marks[1])->col - (marks[0])->col) + 1;
		if (!(new_tetr->shape = make_tetr_shape(new_tetr->height, new_tetr->width)))
			stop();
		fill_tetr(shape, letter, new_tetr);
	}
	return (new_tetr);
}
void set_marks(char *shape, t_mark ***marks)
{
	int len;
	int brick = 0;
	int max_width = 0;
	len = -1;
	while (shape[++len])
	{
		if (shape[len] == (char)35)
		{
			if (len % 5 > max_width)
				max_width = len % 5;
			if (brick == 0)
				(*marks)[0] = create_marks(len);
			else if (brick == 3)
				(*marks)[1] = create_marks(len);
			else if ((len % 5) < (*marks)[0]->col) // если не совпадает левая граница с началом фигурки, например, отраженная по горизонтали L
				(*marks)[0]->col = len % 5;
			brick++;
		}
	}
}
t_mark		*create_marks(int len)
{
	t_mark *point;

	if ((point = (t_mark *)ft_memalloc(sizeof(*point))))
	{
		point->col = len % 5;
		point->row = len / 5;
	}
	return (point);
}
void	fill_tetr(char *shape, char letter, t_tetr *new_tetr)
{
	int	i;
	int j;
	int position_of_brick;
	char **tetr;

	i = 0;
	position_of_brick = new_tetr->position->row * 5 + new_tetr->position->col;
	tetr= new_tetr->shape;
	while (i < new_tetr->height)
	{
		j = 0;
		ft_memcpy(tetr[i], &shape[position_of_brick], (size_t)new_tetr->width);
		while (tetr[i][j] != '\0')
			if (tetr[i][j] == HASH)
					tetr[i][j++] = letter;
		i++;
		position_of_brick += 5;
	}
}
char		**make_tetr_shape(int height, int width)
{
	char	**shape;
	int		i;

	if (!(shape = (char **)ft_memalloc(sizeof(*shape) * height + 1)))
		stop();
	i = 0;
		while (i < height)
		{
			if (!(shape[i] = ft_strnew((size_t)width)))
			{
				while (--i)
					ft_strdel(&shape[i]);
				stop();
			}
			ft_memset(shape[i], '.', (size_t)width);
			i++;
		}
		shape[i] = "\0";
	return(shape);
}



