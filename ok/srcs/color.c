#include "ft_ls.h"

int make_colorful(char *color, char *buf)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (color[c])
		buf[i++] = color[c++];
	return (i);
}


int color_name(t_dir *object, char *buf)
{
	char *purple;
	char *blue;
	char *yellow;
	char *red;
	char *green;
	int i;

	i = 0;
	blue = "\e[96m";
	purple = "\e[95m";
	yellow =  "\e[43m";
	green = "\e[42m";
	red = "\e[91m";
	if (((S_IXUSR & object->mode) == S_IXUSR) || ((S_IXGRP & object->mode) == S_IXGRP) || ((S_IXOTH & object->mode) == S_IXOTH))
		i = make_colorful(red, buf);
	if (define_mode(object->mode) == 'd')
		i = make_colorful(blue, buf);
	if (define_mode(object->mode) == 'l')
		i = make_colorful(purple, buf);
	if (define_mode(object->mode) == 'c')
		i = make_colorful(yellow, buf);
	if (((S_ISVTX & object->mode) == S_ISVTX))
		i = make_colorful(green, buf);
	return (i);
}

int reset_color(char *buf, int background)
{
	char *reset1;
	char *reset2;
	int c;

	int i;
	reset1 = "\e[39m";
	reset2 = "\e[49m";
	i = 0;
	c = 0;
	if (!(background))
	{
		while (reset1[c])
			buf[i++] =  reset1[c++];
	}
	else
		while (reset2[c])
			buf[i++] =  reset2[c++];
	return(i);
}
