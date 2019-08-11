#include "ft_ls.h"

void		cols_output(t_dir *object, uint16_t ws_col, uint16_t total)
{
	t_col_tty	col_struct;
	char		buf[BUFF_MAX];
	int	count;
	uint16_t curr_row;

	if (!object)
		exit(-1);
	total = 0;//unused
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

