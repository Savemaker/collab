#include "ft_ls.h"

char	**check_dir(int argc, char **argv, int flags_quantity)
{

	if (argc - flags_quantity == 1)
	{
		argv[argc] = ".";
		argv[argc + 1] = NULL;
	}
	return (argv);
}

void 		check_access(mode_t mode, char *buf)
{
	if ((S_IRWXU & mode) != S_IRWXU) //for owner
	{
		if ((S_IRUSR & mode) != S_IRUSR) //4
			buf[0] = '-';
		if ((S_IWUSR & mode) != S_IWUSR) //2
			buf[1] = '-';
		if ((S_IXUSR & mode) != S_IXUSR) //1
			buf[2] = '-';
	}
	if ((S_IRWXG & mode) != S_IRWXG) //for group
	{
		if ((S_IRGRP & mode) != S_IRGRP)
			buf[3] = '-';
		if ((S_IWGRP & mode) != S_IWGRP)
			buf[4] = '-';
		if ((S_IXGRP & mode) != S_IXGRP)
			buf[5] = '-';
	}
	if ((S_IRWXO & mode) != S_IRWXO) //for other
	{
		if ((S_IROTH & mode) != S_IROTH)
			buf[6] = '-';
		if ((S_IWOTH & mode) != S_IWOTH)
			buf[7] = '-';
		if ((S_IXOTH & mode) != S_IXOTH)
			buf[8] = '-';
	}
}