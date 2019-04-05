//
// Created by Екатерина on 2019-03-22.
//
#include "../includes/fill.h"

void valid_line(int fd, char *line)
{

	int i;
	int linenum;
	int brick;

	linenum = 1;
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if ((*line == '\0' && (linenum % 5 != 0)) || ((linenum % 5 == 0) && *line))
			stop();
		if (ft_strlen(line) == 0 || ft_strlen(line) == 4) {
			brick = 0;
			while (line[i] != '\0') {
				if (line[i] != '.' && line[i] != '#')
					stop();
				if (line[i] != '#')
					brick++;
				i++;
			}
			if ((i != 0 && i != 4) || brick > 4)
				stop();
		} else
			stop();
		linenum++;
	}
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
