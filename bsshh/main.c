#include "minishell.h"

//static char *find_line(char **content)
//{
//	int i;
//	char *str;
//	char *tmp;
//
//	i = 0;
//
//	while (*(*content + i) && *(*content + i) != '\n')
//		i++;
//	if (*(*content + i) == '\n')
//	{
//		*(*content + i) = '\0';
//		i++;
//	}
//	str = ft_strdup(*content);
//	tmp = ft_strdup(*content + i);
//	free(*content);
//	*content = tmp;
//	return (str);
//}
//
//int get_next_line(const int fd, char **line)
//{
//	int nb;
//	char buf[BUFF_SIZE + 1];
//	static char *inputcont[1];
//	char *tmp;
//
//	if (fd < 0 || line == NULL ||(read(fd, buf, 0) < 0))
//		return (-1);
//	while ((nb = read(fd, buf, BUFF_SIZE)) > 0)
//	{
//		if (!inputcont[fd])
//			inputcont[fd] = ft_strnew(1);
//		buf[nb] = '\0';
//		tmp = ft_strjoin(inputcont[fd], buf);
//		free(inputcont[fd]);
//		inputcont[fd] = tmp;
//		tmp = NULL;
//		if (ft_strchr(buf, '\n') != NULL)
//			break ;
//	}
//	if (nb == 0 && inputcont[fd] == NULL)
//		return (-1);
//	if (*inputcont[fd] == '\0') //
//		return (0);
//	*line = find_line(&inputcont[fd]);
//	return (1);
//}

char **make_env_cp(char **env_dst, char **env_origin)
{
	int i_origin;
	int j_dst;

	i_origin = 0;
	j_dst = 0;
	while (env_origin[i_origin])
		i_origin++;
	if (!(env_dst = (char **)malloc(sizeof(char *) * (i_origin + 1))))
		perror_cmnd("minishell", NULL, MLKERR);
	while (j_dst < i_origin)
	{
		env_dst[j_dst] = ft_strdup(env_origin[j_dst]);
		j_dst++;
	}
	env_dst[j_dst] = NULL;
	return(env_dst);
}

void	print_usage(void)
{
	ft_putstr("usage: minishell\n");
}

int main(int argc, char **argv, char **env)
{
	//env_cp = NULL;
	argv = NULL;
	if (argc == 1)
	{

        g_env = make_env_cp(g_env, env);
	    cmnd_loop();
	///	// exit, cleanup
	}
	else
		print_usage();
	return (0);
}

