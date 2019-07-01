#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>

# define BIT(N) (1 << N)
# define SET_BIT(X,N) ((X) |= (BIT(N)))
# define CHECK_FLAG(X,N) ((X) & (BIT(N)))

#define RESETCOLOR "\x1b[0m"
#define GREEN      "\x1b[32;1m"
#define MAGENTA    "\x1b[35;1m"
#define CYAN       "\x1b[36;1m"

typedef struct		s_dir
{
	char			*name;
	struct s_dir	*inside_files;
	int				level;
	char			*path;
	uint16_t		flags;
	uint16_t		namewidth;
	mode_t			mode;		//Mode of file
	off_t			size;		//file size, in bytes
	gid_t			gid;		//Group ID of the file
	uid_t			uid;		//User ID of the file
	dev_t			dev_type; 	//Device type
	time_t          atime; 		//последний доступ, енсли прочитано больше 0 байт
	time_t 			mtime;		//последняя модификация, если записано больше 0 байт, при созданиии и удалении файлов в каталоге
	time_t 			ctime; 		//последнее изменение, при записи или установке информации о владельце, группе, кол-вах ссылок, режиме и тд
	nlink_t			nlink; 		//Number of hard links
	struct s_dir	*next;
	struct s_dir	*prev;
}					t_dir;


//justfortest!

t_dir	*basic_print(t_dir *list);

typedef struct	s_col_tty
{
	uint16_t	maxwidth;
	uint16_t	cols;
	uint16_t	rows;
	uint16_t	obj_quantity;
}				t_col_tty;

typedef struct	s_row_tty
{
	uint16_t	total;	//общее дисковое пространство, используемое всеми файлами в каталоге
	uint16_t	nlink; 	//кол-во жестких ссылок
	uint16_t	size;
	uint16_t	uid;
	uint16_t	gid;
	time_t		mtime;	//последняя модификация
}				t_row_tty;

void	print_dir_content(t_dir *object, uint16_t flags, uint16_t ws_col, void (ft)(t_dir *, uint16_t));
t_dir	*dir_reading(t_dir *object);
void	fillin_data(struct dirent *entry, t_dir *object, t_dir *file);
t_dir	*get_data(t_dir *file);
void	rows_output(t_dir *object, uint16_t ws_cols);

# define BUFF_MAX 8000500 //это рандом, макс который взял мой ноут //надо посмотреть, что там с сайз т


//ok

DIR					*check_open(char *dpath, char *name);
void				check_close(int ret);
void				check_error(char *dpath, char *name);
char				define_mode(mode_t mode);
void 				identify(t_dir *dirlst, char *name);
void				usage_msg(char c);
char				**check_dir(int argc, char **argv, int flags_quantity);
uint16_t			add_flags(char **argv, uint16_t *flags_q);
uint16_t			define_flag(uint16_t allflags, char receivedflag);
uint16_t			check_flags(uint16_t flags, char flag);
char				*check_name_from_path(char *name);
int 				processing(int argc, char **argv);
t_dir				*make_list(t_dir *object, t_dir **head, t_dir **root);
t_dir				*create_new_node(uint16_t flags);
t_dir				*mount_file(t_dir *object, t_dir **root);
t_dir				*make_argv_lst(char **argv, uint16_t flags, uint16_t *i);
t_dir				*stat_info(t_dir **dir);
t_dir				*checkroot_andcreate(t_dir *dir, t_dir **head, uint16_t flags);
t_dir				*display_files(t_dir *dir_head, t_dir *file_head);
t_dir				*sorting(t_dir *dir, uint16_t flags);
uint16_t			rev_sort(t_dir *dir);
uint16_t			default_sort(t_dir *dir);
uint16_t			mtime_sort(t_dir *dir);
uint16_t			atime_sort(t_dir *dir);
t_dir				*sort_list(t_dir *dir, uint16_t (ft)(t_dir*));
t_dir				*swap_list(t_dir *current, t_dir *next, t_dir *head);
char				*check_path(char *path, char *name);
void 				set_cols(t_col_tty *col_struct);
void				define_cols_rows(t_col_tty *col_struct, uint16_t ws_col);
t_col_tty			colstruct_info(t_dir *object, uint16_t ws_col);
void				create_print_buf(t_dir *object, t_col_tty col_struct, char *buf, uint16_t *count);
void				cols_output(t_dir *dir, uint16_t ws_col);
void				print_path(t_dir *object, uint16_t flags);
void				print(t_dir *dir);

#endif