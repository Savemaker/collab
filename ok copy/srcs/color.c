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


int color_name(t_dir *object, char *buf) //this
{
	char *purple;
	char *blue;
	char *cyellow;
	char *red;
	char *green;
	char *fullblue;
	char *cyan;
	char *pink;
	char *sticky_yellow;
	int i;
struct stat s;

	i = 0;
	blue = "\e[96m";
	purple = "\e[95m";
	cyellow =  "\e[43m";
	green = "\e[42m";
	red = "\e[91m";
	fullblue = "\e[44m";
	cyan = "\e[106m";
	pink = "\e[35m";
	sticky_yellow = "\e[33m";

	lstat(object->path, &s);
	if ((S_IXUSR & s.st_mode) == S_IXUSR || ((S_IXGRP & s.st_mode) == S_IXGRP) || ((S_IXOTH & s.st_mode) == S_IXOTH))
		i = make_colorful(red, buf);
	if (define_mode(object->mode) == 'l')
		i = make_colorful(purple, buf);
	if (define_mode(object->mode) == 'c')
		i = make_colorful(cyellow, buf);
	if (define_mode(object->mode) == 'b')
		i = make_colorful(fullblue, buf);
	if (define_mode(object->mode) == 'p')
		i = make_colorful(cyan, buf);
	if (define_mode(object->mode) == 's')
		i = make_colorful(pink, buf);
	if (define_mode(object->mode) == 'd')
		i = make_colorful(blue, buf);
	if ((define_mode(object->mode) == 'd') && (S_IWOTH & s.st_mode) == S_IWOTH)
		i = make_colorful(sticky_yellow, buf);
	if (((S_ISVTX & object->mode) == S_ISVTX) && (S_IWOTH & s.st_mode) == S_IWOTH)
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
