
#include "../includes/fill.h"
#include <stdio.h>

t_list	*new_tetr(char *tetr_str, char letter)
{
	t_tetr	*tetr;
	t_list	*tetr_lst;

	if (!(tetr = create_tetr(tetr_str, letter)))
		stop();
	if (!(tetr_lst = ft_lstnew((void *)tetr, sizeof(*tetr))))
	{
		free_tetr_lst(&tetr);
		stop();
	}
	return (tetr_lst);
}

void	tetradd(t_list **beginLst, t_list **finalLst, char *tetr_str, int fig_count)
{
	if (fig_count != 0 && ((*finalLst)->next = new_tetr(tetr_str, (char)(64 + fig_count))))
		*finalLst = (*finalLst)->next;
	else if ((*beginLst = new_tetr(tetr_str, (char)(65 + fig_count))))
		*finalLst = *beginLst;
	else
	{
       // void	del_tetr(void *content, size_t content_size);
		//написать функцию удаления списка
		//в либе была какая-то функция, которая чистила поочередно листы
		stop();
	}
}