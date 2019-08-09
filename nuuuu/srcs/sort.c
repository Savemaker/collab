#include "ft_ls.h"

//t_dir	*swap_list(t_dir *current, t_dir *next, t_dir *head)
//{
//	t_dir *prev1;
//	t_dir *next2;
//
//	prev1 = current->prev;
//	next2 = next->next;
//	next->next = current;
//	next->prev = prev1;
//	current->next = next2;
//	current->prev = next;
//	if (next2 != NULL)
//		next2->prev = current;
//	if (current != head)
//		prev1->next = current;
//	return (next);
//}
//t_dir	*sort_list(t_dir *dir, uint16_t (ft)(t_dir*))
//{
//	t_dir	*head;
//
//	if (!dir)
//		return (NULL);
//	if (!dir->next)
//		return(dir);
//	head = dir;
//	while (dir && dir->next)
//	{
//		if (ft(dir))
//		{
//			dir = swap_list(dir, dir->next, head);
//			if (dir->prev)
//			{
//				(dir->prev)->next = dir;
//				dir = dir->prev;
//			}
//			else
//				head = dir;
//			continue ;
//		}
//		dir = dir->next;
//	}
//	return (head);
//}
//
//t_dir	*sorting(t_dir *dir, uint16_t flags)
//{
//	if (!dir)
//		return (NULL);
//	if (check_flags(flags, 'f'))
//		return (dir);
//	if (check_flags(flags, 'r'))
//		return (sort_list(dir, rev_sort));
//	if (check_flags(flags, 't'))
//		return (sort_list(dir, mtime_sort));
//	if (check_flags(flags, 'u'))
//		return (sort_list(dir, atime_sort));
//	if (check_flags(flags, 'S'))// wtf
//		return (sort_list(dir, size_sort));
//	return (sort_list(dir, default_sort));
//}


t_dir		*merge(t_dir *a, t_dir *b, int (f) (t_dir *, t_dir *))
{
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if ((f(a, b) == 0))
	{
		a->next = merge(a->next, b, f);
		return (a);
	}
	else
	{
		b->next = merge(b->next, a, f);
		return (b);
	}
}

void		divide_list(t_dir **list, t_dir **b)
{
	t_dir *fast;
	t_dir *slow;

	slow = *list;
	fast = (*list)->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*b = slow->next;
	slow->next = NULL;
}

void		merge_sorting(t_dir **list, int (f)(t_dir *, t_dir *))
{
	t_dir *a;
	t_dir *b;

	if (*list == NULL || (*list)->next == NULL)
		return ;
	a = *list;
	b = NULL;
	divide_list(list, &b);
	merge_sorting(&a, f);
	merge_sorting(&b, f);
	*list = merge(a, b, f);
}

int			default_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) > 0)
		return (1);
	return (0);
}

int			reverse_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) < 0)
		return (1);
	return (0);
}

int			time_sort(t_dir *dir, t_dir *dira)
{
	struct stat s;
	struct stat sa;
	time_t		d;
	time_t		da;

	lstat(dir->path, &s);
	lstat(dira->path, &sa);
	d = s.st_mtime;
	da = sa.st_mtime;
	if (d < da)
		return (1);
	if (d == da)
		if (ft_strcmp(dir->name, dira->name) > 0)
			return (1);
	return (0);
}

int			time_reverse_sort(t_dir *dir, t_dir *dira)
{
	struct stat s;
	struct stat sa;
	time_t		d;
	time_t		da;

	lstat(dir->path, &s);
	lstat(dira->path, &sa);
	d = s.st_mtime;
	da = sa.st_mtime;
	if (d > da)
		return (1);
	if (d == da)
	{
		if (ft_strcmp(dir->name, dira->name) < 0)
			return (1);
	}
	return (0);
}

int 		size_sort(t_dir *dir, t_dir *dira)
{
	if (dir->size > dira->size)
		return(1);
	return (0);
}

int atime_sort(t_dir *dir, t_dir *dira)
{
	if (dir->atime > dira->atime)
		return (1);
	return (0);
}

t_dir		*sorts(t_dir **head, int flags)
{
	if (check_flags('r', flags) && (check_flags('t', flags) == 0))
		merge_sorting(head, reverse_sort);
	else if (check_flags('t', flags) && (check_flags('r', flags) == 0))
		merge_sorting(head, time_sort);
	else if (check_flags('t', flags) && (check_flags('r', flags) == 1))
		merge_sorting(head, time_reverse_sort);
	else if (check_flags('S', flags))
		merge_sorting(head, size_sort);
	else if (check_flags('f', flags))
		return (*head);
	else if (check_flags('u', flags))
		merge_sorting(head, atime_sort);
	else
		merge_sorting(head, default_sort);
	return (*head);
}