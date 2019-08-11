/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:48:29 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/11 18:48:30 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

t_dir		*sorts(t_dir **head, uint16_t flags)
{
	if (check_flags(flags, 'r') && (check_flags(flags, 't') == 0))
		merge_sorting(head, reverse_sort);
	else if (check_flags(flags, 't') && (check_flags(flags, 'r') == 0))
		merge_sorting(head, time_sort);
	else if (check_flags(flags, 't') && (check_flags(flags, 'r') == 1))
		merge_sorting(head, time_reverse_sort);
	else if (check_flags(flags, 'S'))
		merge_sorting(head, size_sort);
	else if (check_flags(flags, 'f'))
		return (*head);
	else if (check_flags(flags, 'u'))
		merge_sorting(head, atime_sort);
	else
		merge_sorting(head, default_sort);
	return (*head);
}
