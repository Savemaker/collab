#include "../includes/fill.h"
#include "../libft/libft.h"

int check_desk_opportunity(t_mark *start, t_tetr *tetr, int desk_size)
{
	if ((start->row + tetr->height - 1) < desk_size && (start->col + tetr->width - 1) < desk_size)
		return (1);
	return(0);
}


//int col_brick_move(t_tetr *tetr)
//{
//    int i;
//
//    i = 0;
//    while (tetr->shape[0][i] != '#')
//        i++;
//    return (i);
//}

int blank(char **desk, int *desk_size, t_mark *start, t_tetr *tetr)
{
	char **shape;
	int row;
	int col;

	shape = tetr->shape;
	while (!(check_desk_opportunity(start, tetr, *desk_size)))
		return(0);
	row = 0;
	while (shape[row])
	{
		col = 0;
		while (shape[row][col] != '\0')
		{
			if (desk[row + start->row][col + start->col] != '.')// shape[row][col] == '.')
				return (0);
			col++;
		}
		row++; 
	}
	return (1);
}


int next_position(char **desk, t_mark **mark)
{
	(*mark)->col = (*mark)->col++;
	while (desk[(*mark)->row])
	{
		while(desk[(*mark)->row][(*mark)->col] != '\0')
		{
			if (desk[(*mark)->row][(*mark)->col] == '.')
				return (1);
			(*mark)->col++;
		}
		(*mark)->row++;
		(*mark)->col = 0;
	}
		return (0);
}


//char **fillit(t_list **tetr_lst, char **desk, int desk_size, t_mark **start, int fig_count)
//{
//	char **repeat_check;
//
//	t_tetr *tetr;
//	tetr = (t_tetr *)(*tetr_lst)->content;
//	if (blank(desk, &desk_size, *start, tetr))
//	{
//		if ((*start)->col == fig_count - 1) {
//			desk = insert_to_desk(desk, *start, tetr);
//			return (desk);
//		} else if ((repeat_check = fillit(tetr_lst, desk, desk_size, start, fig_count)))
//			return (repeat_check);
//		else
//			delete_tetr_from_desk(desk, tetr);
//	}
//	return (NULL);
//}
//
//void solving(t_list **tetr_lst)
//{
//	char **desk;
//	int fig_count;
//	int desk_size;
//	t_mark *start;
//
//	fig_count = (int)(*tetr_lst)->content_size;
//	start = create_marks(0);
//	desk_size = sizeof_desk(fig_count, tetr_lst);
//	desk = draw_desk(desk_size);
//
//	while (!(fillit(tetr_lst, desk, desk_size, &start, fig_count)))
//	{
//		clean_desk(desk, desk_size);
//
//		if (!next_position(desk, &start))
//		{
//		start->row = 0;
//		start->col = 0;
//		return (0);
//		}
//		desk = draw_desk(desk_size + 1);
//	}
//	print_desk(desk);
//	clean_desk(desk, desk_size);
//	free(desk);
//}





char **fillit(t_list *tetr_lst, char **desk, int desk_size, t_mark **start, int fig_count)
{
	t_tetr *tetr;
	tetr = (t_tetr *)(tetr_lst)->content;

	if (!blank(desk, &desk_size, *start, tetr) && !next_position(desk, start))
		return (0);

    desk = insert_to_desk(desk, *start, tetr);
    if (--fig_count == 0)
        return (desk);
    else if (fig_count)
    {
        tetr_lst = tetr_lst->next;
        fillit(tetr_lst, desk, desk_size, start, fig_count);
    }
    else (delete_tetr_from_desk(desk, tetr));
    return (NULL);
}

int solving(t_list *tetr_lst)
{
	char **desk;
	int fig_count;
	int desk_size;
	t_mark *start;

	fig_count = (int)(tetr_lst)->content_size;
	start = create_marks(0);
	desk_size = sizeof_desk(fig_count, tetr_lst);
	desk = draw_desk(desk_size);

	while (!(fillit(tetr_lst, desk, desk_size, &start, fig_count)))
	{
		clean_desk(desk, desk_size);

		if (!(desk = draw_desk(desk_size + 1)))
			return (0);
		start->row = 0;
		start->col = 0;
	}
	print_desk(desk);
	clean_desk(desk, desk_size);
	free(desk);
	return (1);
}

