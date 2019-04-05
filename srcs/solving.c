#include "../includes/fill.h"



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

//int does_it_fit(t_list)
//{
//
//}

int fillit(char **desk, t_mark *start, t_list **finish)
{
	int fits;

	//fckn algorithm
	if (!fits)
		return (0);
	return (1);
}

void solving(t_list **tetr)
{
	int desk_size;
	char **desk;
	t_mark *start;
	int i;
	t_list *finish;

	i = 0;
	desk_size = 2;
	desk = draw_desk(desk_size);
	start = create_marks(0);
	while (!(fillit(desk, start, &finish)))
	{
		if (finish == *tetr)
		{
			clean_desk(desk, desk_size);
			start->row = 0;
			start-> col = 0;
			desk = draw_desk(desk_size + 1);
		}
	}
	print_desk(desk);
	clean_desk(desk, desk_size);
	free(desk);
}