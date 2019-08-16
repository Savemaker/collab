#include "ft_ls.h"

t_dir	*display_files(t_dir *dir_head, t_dir *file_head)
{
	if (file_head)
	{
		print(sorts(&dir_head, dir_head->flags));
		if (dir_head)
		{
			dir_head->flags = define_flag(dir_head->flags, 1);
			return(sorts(&dir_head, dir_head->flags));
		}
	}
	if (dir_head)
		return(sorts(&dir_head, dir_head->flags));
	return (NULL);
}

void	print(t_dir *dir)
{
	struct winsize window;

	if (!dir)
		return ;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, (char*)&window) < 0) // в случае успеха возвращается 0 (или неотрицательное значение), -1 при ошибке
		exit(-1); //надо ли обработать ошибку?
	if (check_flags(dir->flags, 'd'))
	{
		if (check_flags(dir->flags, 'l') || check_flags(dir->flags, 'g'))
			rows_output(dir, window.ws_col, 0); //не выводит тотал
		else
			cols_output(dir, window.ws_col, 0);
		exit(0);
	}
	if (define_mode(dir->mode) != 'd')
	{
		if (check_flags(dir->flags, 'l') || check_flags(dir->flags, 'g'))
			rows_output(dir, window.ws_col, 0);
		else
			cols_output(dir, window.ws_col, 0);
		free_all_dir(dir);
		return;
	}
	if (check_flags(dir->flags, 'l') || check_flags(dir->flags, 'g'))
		print_dir_content(dir, dir->flags, window.ws_col, rows_output);
	else
		print_dir_content(dir, dir->flags, window.ws_col, cols_output);
}

void	print_dir_content(t_dir *object, uint16_t flags, uint16_t ws_col, void (ft)(t_dir *, uint16_t, uint16_t))
{
	t_dir *file;

	file = object;
	while (object)
	{
		if ((define_mode(object->mode) == 'd' && (ft_strcmp(object->name, ".")) && (ft_strcmp(object->name, ".."))) || ((object->level) == 1))
			object->inside_files = dir_reading(object);
		if (object->inside_files)
		{
			print_path(object, flags);
			flags = define_flag(flags, 1);
			object->inside_files = sorts(&(object->inside_files), flags);
			ft(object->inside_files, ws_col, 1); //тотал активен только для роус
			if ((check_flags(flags, 'R') && (ft_strcmp(object->name, ".")) && (ft_strcmp(object->name, ".."))) || ((check_flags(flags, 'R') && (object->level) == 1)))
				print_dir_content(object->inside_files, flags, ws_col, ft);
			else
				free_all_dir(object->inside_files);
		}
		object = object->next;
	}
	free_all_dir(file); // obj
}

void	print_path(t_dir *object, uint16_t flags)
{
	if (object->next || check_flags(flags, 1))
	{
		if (check_flags(flags, 1))
			ft_putchar('\n');
		ft_putstr(object->path);
		ft_putstr(":\n");
	}
}