//#include "ft_ls.h"
//
//uint16_t	rev_sort(t_dir *dir)
//{
//	if (ft_strcmp(dir->name, (dir->next)->name) < 0)
//		return(1);
//	return (0);
//}
//
//uint16_t	default_sort(t_dir *dir)
//{
//	if (ft_strcmp(dir->name, (dir->next)->name) > 0)
//		return(1);
//	return (0);
//}
//
//uint16_t	mtime_sort(t_dir *dir)
//{
//	if (dir->mtime < (dir->next)->mtime)
//		return(1);
//	return (0);
//}
//
//uint16_t	atime_sort(t_dir *dir)
//{
//	if (dir->atime < (dir->next)->atime)
//		return(1);
//	return (0);
//}
//
//uint16_t	size_sort(t_dir *dir)
//{
//	if (dir->size < (dir->next)->size)
//		return(1);
//	return (0);
//}