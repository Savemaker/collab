#include "ft_ls.h"

t_dir	*create_new_node(uint16_t flags)
{
	t_dir	*lst;

	if (!(lst = (t_dir *)malloc(sizeof(t_dir))))
	{
		perror("ft_ls");
		exit(-1);
	}
	lst->next = NULL;
	lst->prev = NULL;
	lst->name = NULL;
	lst->path = NULL;
	lst->flags = flags;
	lst->namewidth = 0;
	lst->gid = 0;
	lst->uid = 0;
	lst->mode = 0;
	lst->level = 0;
	lst->size = 0;
	return (lst);
}

t_dir	*mount_file(t_dir *object, t_dir **root) //into dir head
{
	t_dir	*root_obj;

	root_obj = *root;
	while (root_obj->next && define_mode(root_obj->next->mode) == 'd')
		root_obj = root_obj->next;
	if (!(root_obj->next))
	{
		object = NULL;
		*root = NULL;
	}
	else
	{
		object = root_obj;
		root_obj->next = NULL;
	}
	return (object);
}

t_dir	*make_list(t_dir *object, t_dir **file_head, t_dir **root)
{
	t_dir	*tmp;

	if (!(*file_head)) //для  создания file_head в первый раз
	{
		*file_head = object;
		(*file_head)->prev = NULL;
	}
	else
	{
		tmp = *file_head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = object;
		object->prev = tmp;
	}
	return(mount_file(object, root));
	//return (object);
}

t_dir	*checkroot_andcreate(t_dir *dir, t_dir **head, uint16_t flags)
{
	t_dir *new; // read memory failed

	if (!(*head))
	{
		dir = create_new_node(flags);
		*head = dir;
	}
	else
	{
		new = create_new_node(flags);
		dir->next = new;
		new->prev = dir;
		dir = new;
	}
	return (dir);
}

void	 identify(t_dir *dirlst, char *name)
{
	dirlst->name = check_name_from_path(name);
	dirlst->namewidth = (uint16_t)ft_strlen(name);
	dirlst->path = ft_strdup(name);
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
t_dir	*make_argv_lst(char **argv, uint16_t flags, uint16_t *i)
{
	t_dir *root; //указывает на 1 элемень дирлст
	t_dir *dir; //конкретный элемент
	t_dir *filelst;

	dir = NULL;
	root = dir;

	filelst = NULL;
	while (argv[++(*i)]) //файлы и дир в аргументах
	{
		dir = checkroot_andcreate(dir, &root, flags); // проверяется создан ли корень списка, создает лист
		identify(dir, argv[*i]);
		if (!(stat_info(&dir)))
		{
			delete_from_root(&dir, &root);
			continue;
		}
		if (define_mode(dir->mode) == 'd')
			dir->level = 1;
		if (define_mode(dir->mode) != 'd' && !(check_flags(flags, 'd'))) //файлики и тп // при д нам в принципе нужны только директории без содержимого
			dir = make_list(dir, &filelst, &root);
	}
	//return (root);
	return (display_files(root, filelst));
}
