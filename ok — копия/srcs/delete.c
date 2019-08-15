#include "ft_ls.h"

void	free_all_dir(t_dir *dir)
{
	t_dir *file;

	if (!dir)
		return;
	while (dir) {
		file = dir;
		dir = dir->next;
		free_list(&file);
	}
}

void	delete_from_root(t_dir **object, t_dir **root)
{
	if ((*object)->prev)
	{
		*object = (*object)->prev;
		free_list(&((*object)->next));
	}
	else
	{
		free_list(object);
		*root = *object;
	}
}

void	free_list(t_dir **lst)
{
	if (!lst)
		return ;
	ft_memdel((void**)&((*lst)->name));
	ft_memdel((void**)&((*lst)->path));
	(*lst)->inside_files = NULL;
	(*lst)->next = NULL;
	(*lst)->prev = NULL;
	free(*lst);
	*lst = NULL;
}

