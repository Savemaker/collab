
#include "../includes/fill.h"
#include <stdio.h>

void				check_count_of_tetr(int count)
{
	if (count > 26 || count < 0)
		stop();
}

void open_file(char *fileContent) {
    t_list *tetr;
    int fd;

    if ((fd = open(fileContent, O_RDONLY)) == 1)
        stop();
    if (!(tetr = read_input(fd))) {
        close(fd);
        stop();
    }
    solving(&tetr);
}

t_list	*read_input(int fd)
{
	char	*tetrLine;
	int fig_count;
	t_list	*finalLst;
	t_list	*beginLst;

	tetrLine = ft_strnew(21);
	fig_count = 0;
	while (read(fd, tetrLine, 21))
	{
		check_count_of_tetr(fig_count + 1);
		valid_newlines(tetrLine);
		valid_line(fd, tetrLine);
		tetrLine[20] = '\0';
		tetradd(&beginLst, &finalLst, tetrLine, fig_count);
	//	ft_bzero(tetrLine, 21);
		fig_count++;
	}
	ft_strdel(&tetrLine);
	if (fig_count == 0)
		stop();
	return (beginLst);
}
