#include "ft_ls.h"

void 		set_cols(t_col_tty *col_struct)
{
	uint16_t quantity;

	quantity = col_struct->obj_quantity;
	if (quantity % col_struct->rows == 0)
		col_struct->cols = quantity / col_struct->rows;
	else
		col_struct->cols = quantity / col_struct->rows + (uint16_t)1;
}

void		define_cols_rows(t_col_tty *col_struct, uint16_t ws_col)
{
	uint16_t quantity;
	uint16_t maxwidth;

	quantity = col_struct->obj_quantity;
	maxwidth = col_struct->maxwidth;
	col_struct->cols = quantity;
	col_struct->rows = 1;
	if (maxwidth >= ws_col) //если название боьлше ширины терминала, он рисует вывод в 1 столбик
	{
		col_struct->cols = 1;
		col_struct->rows = quantity;
		return ;
	}
	while (((maxwidth + 1) * quantity) / col_struct->rows > ws_col) //колонки долдны быть шириной с максимальное название
		(col_struct->rows)++;
	//set_cols(col_struct); // max кол-во колонок
	while (col_struct->cols * (maxwidth + 1) > ws_col)
		set_cols(col_struct);
}

t_col_tty	colstruct_info(t_dir *object, uint16_t ws_col)
{
	t_col_tty	col_struct;

	col_struct.maxwidth = 0;
	col_struct.obj_quantity = 0;
	while (object)
	{
		if (object->namewidth > col_struct.maxwidth)
			col_struct.maxwidth = object->namewidth;
		object = object->next;
		col_struct.obj_quantity++;
	}
	define_cols_rows(&col_struct, ws_col);
	return (col_struct);
}
void		create_print_buf(t_dir *object, t_col_tty col_struct, char *buf, uint16_t *count)
{
	uint16_t curr_col;
	uint16_t j;
	uint16_t i;

	curr_col = 0;
	while (object && ++curr_col <= col_struct.cols)
	{
		j = 0;
		while (object->name[j])
		{
			//check buf // каунт =написать функцию // если он переполнен, то надо его распечатать и верунть каунт == 0
			buf[(*count)++] = object->name[j++];
		}
		while (j++ <= col_struct.maxwidth && curr_col != col_struct.cols)
		{
			//check buf
			buf[(*count)++] = ' ';
		}
		i = 0;
		while (object && ++i <= col_struct.rows)
			object = object->next;
	}
	//check buf
	buf[(*count)++] = '\n';
}

void		cols_output(t_dir *object, uint16_t ws_col)
{
	t_col_tty	col_struct;
	char		buf[BUFF_MAX];
	uint16_t	count;
	uint16_t curr_row;

	if (!object)
		exit(-1);

	count = 0;
	col_struct = colstruct_info(object, ws_col);
	curr_row = 0;
	while (object && ++curr_row <= col_struct.rows)
	{
		create_print_buf(object, col_struct, buf, &count);
		object = object->next;
	}
	write(1, buf, count);
}
