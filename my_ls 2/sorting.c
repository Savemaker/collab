#include "ft_ls.h"

uint16_t	rev_sort(t_dir *dir)
{
	if (ft_strcmp(dir->name, (dir->next)->name) < 0)
		return(1);
	return (0);
}

uint16_t	default_sort(t_dir *dir)
{
	if (ft_strcmp(dir->name, (dir->next)->name) > 0)
		return(1);
	return (0);
}

uint16_t	mtime_sort(t_dir *dir)
{
	if (dir->mtime < (dir->next)->mtime)
		return(1);
	return (0);
}

uint16_t	atime_sort(t_dir *dir)
{
	if (dir->atime < (dir->next)->atime)
		return(1);
	return (0);
}

t_dir	*swap_list(t_dir *current, t_dir *next, t_dir *head)
{
	t_dir *prev1;
	t_dir *prev2;
	t_dir *next1;
	t_dir *next2;

	prev1 = current->prev;
	prev2 = next->prev;
	next1 = current->next;
	next2 = next->next;
	next->next = current;
	next->prev = prev1;
	current->next = next2;
	current->prev = next;
	if (next2 != NULL)
		next2->prev = current;
	if (current != head)
		prev1->next = current;
	return (next);
}
t_dir	*sort_list(t_dir *dir, uint16_t (ft)(t_dir*))
{
	t_dir	*head;

	if (!dir)
		return (NULL);
	if (!dir->next)
		return(dir);
	head = dir;
	while (dir && dir->next)
	{
		if (ft(dir))
		{
			dir = swap_list(dir, dir->next, head);
			if (dir->prev)
			{
				(dir->prev)->next = dir; // меняем указатели, если перед дир есть элементы
				dir = dir->prev;  //чтобы начинать сортировку сначала
			}
			else
				head = dir;
			continue ;
		}
		dir = dir->next;
	}
	return (head);
}
t_dir	*sorting(t_dir *dir, uint16_t flags)
{
	if (!dir)
		return (NULL);
	if (check_flags(flags, 'f'))
		return (dir);
	if (check_flags(flags, 'r'))
		return (sort_list(dir, rev_sort));
	if (check_flags(flags, 't'))
		return (sort_list(dir, mtime_sort));
	if (check_flags(flags, 'u'))
		return (sort_list(dir, atime_sort));
	return (sort_list(dir, default_sort));
}


