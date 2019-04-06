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

//	if (!(fits = does))
//		return (0);
	return (1);
}
int	sizeof_desk(t_list *list)
{
    t_list *head;
    t_tetr *tetr;
    int n;
    n = 0;
    head = list;
    tetr = head->content;
    while (head)
    {
        head = head->next;
        n++;
    }
   if (tetr->height == 2 && tetr-> width== 2)
        return (2);
   else if (tetr->height == 4 || tetr->width == 4)
       return (4);
   else if (tetr->height == 3 || tetr->width == 3)
       return (3);
   else
       return (0);
}
void solving(t_list **tetr)
{
	int desk_size;
	char **desk;
	t_mark *start;
	t_list *finish;

	desk_size = sizeof_desk(*tetr);
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