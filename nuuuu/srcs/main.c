#include "ft_ls.h"

int 	processing(int argc, char **argv)
{
	uint16_t flags;
	uint16_t flags_quantity;

	flags = add_flags(argv, &flags_quantity);
	argv = check_dir(argc, argv, flags_quantity);
	print(make_argv_lst(argv, flags, &flags_quantity));
	return (1);
}

int main(int argc, char **argv)
{
	if (!(processing(argc, argv)))
		exit(0); // возвращаемое значение? !чек!
	return (0);
}