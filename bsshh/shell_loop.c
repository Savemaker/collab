
#include "minishell.h"



# define BUFF_SIZE 333
t_list	*get_true_list_with_fd(int fd, t_list **file)
{
    t_list	*lst;

    lst = *file;
    while (lst)
    {
        if ((int)lst->content_size == fd)
            return (lst);
        lst = lst->next;
    }
    lst = ft_lstnew("", fd);
    ft_lstadd(file, lst);
    return (lst);
}

char	*find_line(void **data)
{
    int		i;
    char	*str;
    char	*tmp;
    char	***content;

    content = (char ***)&data;
    i = 0;
    while (*(**content + i) && *(**content + i) != '\n')
        i++;
    if (*(**content + i) == '\n')
    {
        *(**content + i) = '\0';
        i++;
    }
    str = ft_strdup(**content);
    tmp = ft_strdup(**content + i);
    free(**content);
    **content = tmp;
    return (str);
}

int		read_file(const int fd, char **content)
{
    int		nbyte;
    char	*tmp;
    char	buf[BUFF_SIZE + 1];

    while ((nbyte = read(fd, buf, BUFF_SIZE)))
    {
        buf[nbyte] = '\0';
        tmp = *content;
        if (!(*content = ft_strjoin(*content, buf)))
            return (-1);
        free(tmp);
        if (ft_strchr(buf, '\n') != NULL)
            break ;
    }
    return (nbyte);
}

int		get_next_line(const int fd, char **line)
{
    static	t_list	*file;
    t_list			*actual;
    char			buf[BUFF_SIZE + 1];
    char			*input;
    int				nb;

    if (fd < 0 || line == NULL || (read(fd, buf, 0) < 0))
        return (-1);
    actual = get_true_list_with_fd(fd, &file);
    input = actual->content;
    nb = read_file(fd, &input);
    actual->content = input;
    if (nb == 0 && *((char *)actual->content) == '\0')
        return (0);
    *line = find_line(&(actual->content));
    return (1);
}


int execute_cmnd(char **cmnd)
{
	int execute_status;
	char *path;

	execute_status = 1;// del
	if (cmnd[0] == NULL) //empty command
		return (1); //continue to execute
	else if (*cmnd[0] == '/' || *cmnd[0] == '.')
		execute_status = absolute_path_launch(cmnd);
	else if (check_builtin(cmnd[0]) == 1)
		execute_status = builtin(cmnd);
	else if ((path = check_extern_command(cmnd)))
		execute_status = external_launch(cmnd, path);
	else
		perror_cmnd("minishell", cmnd[0], CMNDNTFND);
	return (execute_status);
}

void cmnd_loop()
{
	char *line;
	char **args;
	int status;
	int i;
	char **mult_args;

	args = NULL;
	status = 1;
	while (status)
	{
		signals();
//		rl_attempted_completion_function = cmnd_completion; //WAT
		while (sigsetjmp(g_sig, 1) != 0)
		  {
		    ft_putchar_fd('\n', STDOUT_FILENO);
		    ;
		  }
        ft_putstr(SHELL_NAME);
        if ((get_next_line(STDIN_FILENO, &line)))
//		if ((line = readline(SHELL_NAME)))
		{
			if ((strrchr(line, ';')))
			{
				if (!(args = ft_strsplit(line, ';')))
					perror_cmnd("minishell", NULL, MLKERR);
				i = 0;
				while (args[i])
				{
				    mult_args = split_cmnd(args[i], ' ');

					status = execute_cmnd(mult_args);

                    int k = 0;
                    while (mult_args[k] != NULL)
                    {
//                    ft_strdel(&args[i]);
                        ft_memdel((void**)&(mult_args[k]));
                        k++;
                    }
                    free(mult_args);
					if (status == 0)
						break ;
					i++;
				}
			}
			else
			{
				args = split_cmnd(line, ' ');
				status = execute_cmnd(args);
                clean_env(args);
			}
//			add_history(line);
			free(line);
		}
		else
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			return ;
		}
	}
}
