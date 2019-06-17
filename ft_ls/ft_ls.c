#include "libft.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#define RESETCOLOR "\x1b[0m"
#define GREEN      "\x1b[32;1m"
#define MAGENTA    "\x1b[35;1m"
#define CYAN       "\x1b[36;1m"



DIR *check_open(char *dpath)
{
	DIR *dir;

	dir = opendir(dpath);
	if (dir == NULL)
	{
		ft_putstr(dpath);
		perror(": Open error");
		return (NULL);
	}
	return (dir);
}

int     no_dots(char *name)
{
	if (name[0] == '.')
		return (0);
	if (ft_strcmp(name, ".") == 0)
		return (0);
	if (ft_strcmp(name, "..") == 0)
		return (0);
	return (1);
}

char *create_path(char *name, char *path)
{
	char *res;
	char *p;
	char *s;
	
	res = (char *)malloc(sizeof(char) * ft_strlen(path));
	ft_memmove(res, path, ft_strlen(path));
	p = ft_strjoin(res, "/");
	s = ft_strjoin(p, name);
	return (s);
}

t_list  *create_node(char *name, char *path)
{
	t_list *new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->name = ft_strdup(name);
	new->path = create_path(name, path);
	new->next = NULL;
    new->prev = NULL;
    return (new);
}

void    append(t_list **head, t_list *node)
{
	t_list *temp;

	temp = *head;
	if (*head == NULL)
		*head = node;
	else
    {
		while (temp->next)
			temp = temp->next;
		temp->next = node;
		node->prev = temp;
	}
}

int		type_of_file(char *path)
{
	struct stat s;

	lstat(path, &s);
	if (S_ISDIR(s.st_mode) == 1)
		return (1);
	return (0);
}

void	print_name(char *name, int f)
{
	char *reset;
	char *s;
	int i;

	i = 0;
	reset = ft_strdup(RESETCOLOR);
	s = ft_strjoin(name, reset);
	if (f == 1)
		s = ft_strjoin(CYAN, s);
	while (s[i])
		write(1, &s[i++], 1);

}

void	print_list(t_list *list)
{
	int f;
	
	while (list)
	{
		f = type_of_file(list->path);
		print_name(list->name, f);
		if (list->next != NULL)
			write(1, " ", 1);
		list = list->next;
	}
	write(1, "\n", 1);	
}


t_list *traverse_back(t_list *list)
{
	t_list *start;

	while (list->prev)
		list = list->prev;
	start = list;
	return (start);
}



void	reverse_checker(t_list *list)
{
	while (list->next)
		list = list->next;
	while (list)
	{
		printf("%s ", list->name);
		list = list->prev;
	}
}

t_list *merge(t_list *a, t_list *b)
{
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if (ft_strcmp(a->name, b->name) <= 0)
	{
		a->next=merge(a->next, b);
		a->next->prev=a;
		a->prev=NULL;
		return (a);
	}
	else
	{
		b->next=merge(b->next, a);
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

void	merge_sorting(t_list **list)
{
	t_list *a;
	t_list *b;

	if (*list == NULL || (*list)->next == NULL)
		return ;
	a = *list;
	b = NULL;
	divide_list(list, &b);
	merge_sorting(&a);
	merge_sorting(&b);
	*list = merge(a, b);
}

void    output_base_path(char *path)
{
	DIR *dir;
	struct dirent *d;
	t_list *head;
	t_list *node;

	head = NULL;
	dir = check_open(path);
	while ((d = readdir(dir)) != NULL)
	{
		if (no_dots(d->d_name))
		{
			node = create_node(d->d_name, path);
			append(&head, node);
		}
	}
	merge_sorting(&head);
	print_list(head);
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		output_base_path(".");
	}
	if (argc == 2)
		output_base_path(argv[1]);
	return (0);
}