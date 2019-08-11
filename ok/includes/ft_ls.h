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
#include <sys/acl.h>

# define BIT(N) (1 << N)
# define SET_BIT(X,N) ((X) |= (BIT(N)))
# define CHECK_FLAG(X,N) ((X) & (BIT(N)))
# define ATTR_VALSIZE 300 //attr value
# define ATTR_NAMESTR 1024
# define BUFF_MAX 1000000

typedef struct		s_dir
{
	char			*name;
	struct s_dir	*inside_files;
	int				level;
	char			*path;
	uint16_t		flags;
	uint16_t		namewidth;
	blkcnt_t		blocks;		// blocks allocated for file
	mode_t			mode;		//Mode of file
	off_t			size;		//file size, in bytes
	gid_t			gid;		//Group ID of the file
	uid_t			uid;		//User ID of the file
	dev_t			rdev; 		//Device type/id
	time_t          atime; 		//последний доступ, енсли прочитано больше 0 байт
	time_t 			mtime;		//последняя модификация, если записано больше 0 байт, при созданиии и удалении файлов в каталоге
	time_t 			ctime; 		//последнее изменение, при записи или установке информации о владельце, группе, кол-вах ссылок, режиме и тд
	nlink_t			nlink; 		//Number of hard links
	struct s_dir	*next;
	struct s_dir	*prev;
}					t_dir;

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
	uint16_t	nlink_len;
	uint16_t 	size_len;
	uint16_t	uid_len;
	uint16_t 	gid_len;
	int			xattr_label_len;
	char 		xattr[ATTR_NAMESTR];
	ssize_t		xattr_lstsize;
	uint16_t	major_len; //старший млдаший номреа устройств
	uint16_t	minor_len;
}				t_row_tty;

typedef struct	s_word
{
	int i;
	int j;
}				t_word;


//int		create_print_buf(t_dir *object, t_col_tty col_struct, char *buf);
void skip_word(char *res, struct s_word *str);
void draw_word(char *res, char *buf, struct s_word *str);
int  draw_zero(char *buf);
uint16_t get_sizelen(int num);
void check_error(char *dpath, char *name);
DIR *check_open(char *dpath, char *name);
void check_close(int ret);
void	free_all_dir(t_dir *dir);
t_dir	*mount_file(t_dir *object, t_dir **root); //into dir head
char	*check_path(char *path, char *name);
char	**check_dir(int argc, char **argv, int flags_quantity);
t_dir	*checkroot_andcreate(t_dir *dir, t_dir **head, uint16_t flags);
void	delete_from_root(t_dir **object, t_dir **root);
void	free_list(t_dir **lst);
char	*check_name_from_path(char *name);
char	define_mode(mode_t mode);
void 		check_access(mode_t mode, char *buf);
void	usage_msg(char c);
uint16_t	define_flag(uint16_t allflags, char receivedflag);
uint16_t	add_flags(char **argv, uint16_t *flags_q);
uint16_t	check_flags(uint16_t flags, char flag);
t_dir	*create_new_node(uint16_t flags);
t_dir	*stat_info(t_dir **dir);
t_dir	*dir_reading(t_dir *object);
void	fillin_data(struct dirent *entry, t_dir *object, t_dir *file, t_dir **head);
t_dir	*get_data(t_dir *file);
t_dir	*make_argv_lst(char **argv, uint16_t flags, uint16_t *i);
void	 identify(t_dir *dirlst, char *name);
t_dir	*make_list(t_dir *object, t_dir **file_head, t_dir **root);
int 	processing(int argc, char **argv);
t_dir	*display_files(t_dir *dir_head, t_dir *file_head);
void	print_path(t_dir *object, uint16_t flags);
void	print_dir_content(t_dir *object, uint16_t flags, uint16_t ws_col, void (ft)(t_dir *, uint16_t, uint16_t));
void		cols_output(t_dir *object, uint16_t ws_col, uint16_t total);
void		create_print_buf(t_dir *object, t_col_tty col_struct, char *buf, int *count);
//uint16_t check_buf(char *buf, uint16_t i);
t_col_tty	colstruct_info(t_dir *object, uint16_t ws_col);
void		define_cols_rows(t_col_tty *col_struct, uint16_t ws_col);
void 		set_cols(t_col_tty *col_struct);
void		print_total(t_row_tty *row_struct);
int			print_access(t_dir *object, char *buf, t_row_tty *row_struct);
void	nbtostr(long int n, int i, char *buf);
int			print_name(t_dir *object, char *buf);
int			print_size(long int size, char *buf, long int max_len);
int			print_major_minor(long int size, char *buf, long int max_len, uint16_t major);
int			print_uid(uid_t uid, char *buf, t_row_tty **row_struct);
int 		print_gid(gid_t gid, char *buf, t_row_tty **row_struct);
void		rows_output(t_dir *object, uint16_t ws_cols, uint16_t total);
void		print(t_dir *dir);
int			print_attributes(t_dir *object, char *buf, t_row_tty *row_struct);
void 		set_cols_plus(t_col_tty *col_struct);
t_dir		*sorts(t_dir **head, uint16_t flags);
int     print_time(char *buf, t_dir *list);
uint16_t			default_sort(t_dir *dir, t_dir *dira);
uint16_t			reverse_sort(t_dir *dir, t_dir *dira);
uint16_t			time_sort(t_dir *dir, t_dir *dira);
uint16_t			time_reverse_sort(t_dir *dir, t_dir *dira);
uint16_t 		size_sort(t_dir *dir, t_dir *dira);
uint16_t			atime_sort(t_dir *dir, t_dir *dira);
void		merge_sorting(t_dir **list, uint16_t (f)(t_dir *, t_dir *));
t_dir		*merge(t_dir *a, t_dir *b, uint16_t (f)(t_dir *, t_dir *));
int make_colorful(char *color, char *buf);
int color_name(t_dir *object, char *buf);
int reset_color(char *buf, int background);
void check_buf(char *buf, uint16_t i);

#endif
