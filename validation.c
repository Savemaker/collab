#include "../includes/fill.h"
#include "../libft/libft.h"

void valid_line(char *line)
{
	int len;
	int brick;

	brick = 0;
	len = 0;
	while (line[len])
	{
		if ((len + 1 % 5 == 0 && line[len] != '\n') || (line[len] != '\n' && line[len] != '.' && line[len] != '#'))
			stop();
		if (line[len] == '#')
			brick++;
		len++;
	}
	if (!brick || brick != 4)
		stop();

}

void		valid_newlines(char *tetrLine)
{
	int i;

	i = 19;
	while (i > 0)
	{
		if (tetrLine[i] != '\n')
			stop();
		i = i - 5;
	}
	if (tetrLine[20] != '\n' && tetrLine[20] != '\0')
		stop();
}

void valid_fig_continue(char *tetrstr)
{
	if (*(tetrstr + 1) == '#' && *(tetrstr + 2) == '#' && *(tetrstr + 7) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 11) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 4) == '#' && *(tetrstr + 5) == '#')
		;
	else if (*(tetrstr + 4) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 9) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 7) == '#')
		;
	else if (*(tetrstr + 4) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 6) == '#')
		;
	else if (*(tetrstr + 4) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 10) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 10) == '#')
		;
    else if (*(tetrstr + 1) == '#' && *(tetrstr + 2) == '#' && *(tetrstr + 6) == '#')
        ;
	else
		stop();
}

void	valid_fig(char *tetrstr)
{
	while (*tetrstr != '#')
		tetrstr++;
	if (*(tetrstr + 5) == '#' && *(tetrstr + 10) == '#' && *(tetrstr + 15) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 2) == '#' && *(tetrstr + 3) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 6) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 10) == '#' && *(tetrstr + 11) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 11) == '#')
		;
	else if (*(tetrstr + 2) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 11) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 2) == '#' && *(tetrstr + 5) == '#')
		;
	else if (*(tetrstr + 3) == '#' && *(tetrstr + 4) == '#' && *(tetrstr + 5) == '#')
		;
	else if (*(tetrstr + 1) == '#' && *(tetrstr + 5) == '#' && *(tetrstr + 10) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 9) == '#' && *(tetrstr + 10) == '#')
		;
	else if (*(tetrstr + 5) == '#' && *(tetrstr + 6) == '#' && *(tetrstr + 7) == '#')
		;
	else
		valid_fig_continue(tetrstr);
}
