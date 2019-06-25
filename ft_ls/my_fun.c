//точно работает с фт_стрсмп, но если найдутся баги скажи плз!!


t_list *merge(t_list *a, t_list *b, int (*f)(const char *, const char *))
{
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if (f(a->name, b->name) <= 0)
	{
		a->next=merge(a->next, b, f);
		a->next->prev=a;
		a->prev=NULL;
		return (a);
	}
	else
	{
		b->next=merge(b->next, a, f);
		b->next->prev=b;
		b->prev=NULL;
		return (b);
	}
	
}

void	divide_list(t_list **list, t_list **b)
{
	t_list *fast;
	t_list *slow;

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

void	merge_sorting(t_list **list, int (*f)(const char *, const char *))
{
	t_list *a;
	t_list *b;

	if (*list == NULL || (*list)->next == NULL)
		return ;
	a = *list;
	b = NULL;
	divide_list(list, &b);
	merge_sorting(&a, f);
	merge_sorting(&b, f);
	*list = merge(a, b, f);
}