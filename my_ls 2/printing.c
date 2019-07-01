#include "ft_ls.h"

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

t_dir	*get_data(t_dir *file)
{
	struct stat	buf;

	if (!(file))
		return (NULL);
	if (lstat((file)->path, &buf) == -1)
	{
		check_error((file)->path, (file)->name);
		return (NULL);
	}
	file->uid = buf.st_uid;
	file->gid = buf.st_gid;
	file->nlink = buf.st_nlink;
	file->atime = buf.st_atime;
	file->mtime = buf.st_mtime;
	file->mode = buf.st_mode;
	if (define_mode((file)->mode) == 'b' || define_mode((file)->mode) == 'c')
		(file)->dev_type = buf.st_rdev;
	else
		(file)->size = buf.st_size;
	return (file);
}

void	fillin_data(struct dirent *entry, t_dir *object, t_dir *file)
{
	file->mode = DTTOIF(entry->d_type); //Convert between stat structure types and directory types
	file->name = ft_strdup(entry->d_name);
	file->path = check_path(object->path, entry->d_name);
	file->namewidth = entry->d_namlen;
	file->level = (object->level) + 1;
	if (check_flags(object->flags, 'l') || check_flags(object->flags, 't') || check_flags(object->flags, 'u') || check_flags(object->flags, 'g'))
		get_data(file); //
}

t_dir	*dir_reading(t_dir *object)
{
	t_dir			*head;
	t_dir			*file;
	struct dirent	*entry;
	DIR				*dir;

	if (define_mode(object->mode) != 'd' || !(dir = check_open(object->path, object->name)))
		return (NULL);
	file = NULL;
	head = file;
	while ((entry = readdir(dir)))
	{
		if ((entry->d_name)[0] == '.')
			continue ;
		file = checkroot_andcreate(file, &(head), object->flags);
		fillin_data(entry, object, file);
	}
	check_close(closedir(dir));
	return (head);
}

void	print_dir_content(t_dir *object, uint16_t flags, uint16_t ws_col, void (ft)(t_dir *, uint16_t))
{
	while (object)
	{
		if ((define_mode(object->mode) == 'd' && ft_strcmp(object->name, ".") && ft_strcmp(object->name, "..")) || ((object->level) > 0))
			object->inside_files = dir_reading(object);
		if (object->inside_files)
		{
			print_path(object, flags);
		//	flags = define_flag(flags, 1);
			object->inside_files = sorting(object->inside_files, define_flag(flags, 1));
			ft(object->inside_files, ws_col);
			if ((check_flags(flags, 'R') && ft_strcmp(object->name, ".") && ft_strcmp(object->name, "..")) || (check_flags(flags, 'R') && (object->level) > 0))
				print_dir_content(object->inside_files, flags, ws_col, ft);
//			else
//				free
		}
		object = object->next;
	}
//	free all;
}

void	print(t_dir *dir)
{
	struct winsize window;

	if (!dir)
		return ;
	//в структуру записать row, col терминала
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, (char*)&window) < 0) // в случае успеха возвращается 0 (или неотрицательное значение), -1 при ошибке
		exit(-1); //надо ли обработать ошибку?
	if (check_flags(dir->flags, 'd')) // прост печатаем названия
	{
		if (check_flags(dir->flags, 'l') || check_flags(dir->flags, 'g'))
			rows_output(dir, window.ws_col);
		else
			cols_output(dir, window.ws_col);
		exit(0);
	}
	if (define_mode(dir->mode) != 'd') //выводим названя или при флагах инфу о файлах
	{
		if (check_flags(dir->flags, 'l') || check_flags(dir->flags, 'g'))
			rows_output(dir, window.ws_col);
		else
			cols_output(dir, window.ws_col);
		//free dir
		return;
	}
	if (check_flags(dir->flags, 'l') || check_flags(dir->flags, 'g'))
		print_dir_content(dir, dir->flags, window.ws_col, rows_output);
	else
		print_dir_content(dir, dir->flags, window.ws_col, cols_output);
}

t_dir	*display_files(t_dir *dir_head, t_dir *file_head)
{
	if (file_head)
	{
		print(sorting(file_head, file_head->flags));
		if (dir_head)
		{
			dir_head->flags = define_flag(dir_head->flags, 1);
			return (sorting(dir_head, dir_head->flags));
		}
	}
	if (dir_head)
		return (sorting(dir_head, dir_head->flags));
	return (NULL);
}
