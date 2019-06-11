#include "../includes/fill.h"
#include "../libft/libft.h"

char **draw_desk(int size)
{

	char **desk;
	int i;

	i = 0;
	if (!(desk = (char**)ft_memalloc(sizeof(*desk) * (size + 1))))
		stop();
	while (i < size)
	{
		if (!(desk[i] = ft_strnew((size_t)size)))
		{
			while (--i)
				ft_strdel(&desk[i]);
			free(desk);
			stop();
		}
		ft_memset(desk[i], '.', (size_t)size);
		i++;
	}
	return (desk);
}
void print_desk(char **desk)
{
	int i;

	i = 0;
	while (desk[i] != '\0')
	{
		ft_putstr(desk[i]);
		ft_putchar('\n');
		i++;
	}
}

char** insert_to_desk(char **desk, t_mark *start, t_tetr *tetr)
{
	int row;
	int col;
	char **tetr_shape;

	tetr_shape = tetr->shape;
	row = 0;
	while (tetr_shape[row] != NULL)
	{
		col = 0;
		while (tetr_shape[row][col] != '\0')
		{
			if (tetr_shape[row][col] != '.')
			{
				desk[row + start->row][col + start->col] = tetr_shape[row][col];
			}
			col++;
		}
		row++;
	}
	tetr->position->row = start->row;
	tetr->position->col = start->col;
	return (desk);
}
void delete_tetr_from_desk(char **desk, t_tetr *tetr)
{
	char **shape;
	int row;
	int col;

	row = 0;
	shape = tetr->shape;
	while (shape[row])
	{
		col = 0;
		while (shape[row][col] != '\0')
		{
			if (shape[row][col] != '.')
			{
				desk[row + tetr->position->row][col+ tetr->position->col] = '.';
			}
			col++;
		}
		row++;
	}
}

int	sizeof_desk(int fig_count, t_list *tetr_lst)
{
	int i;
	t_tetr *tetr;


	i = 2;

	tetr = (t_tetr *)(tetr_lst)->content;
    if (fig_count == 1 && (tetr->width == 2 || tetr->height == 2))
        return (2);
	while (i * i < fig_count * 4)
		i++;
	return (i);
}
