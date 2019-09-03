
#include "minishell.h"

static char *find_line(char **content)
{
	int i;
	char *str;
	char *tmp;

	i = 0;

	while (*(*content + i) && *(*content + i) != '\n')
		i++;
	if (*(*content + i) == '\n')
	{
		*(*content + i) = '\0';
		i++;
	}
	str = ft_strdup(*content);
	tmp = ft_strdup(*content + i);
	free(*content);
	*content = tmp;
	return (str);
}

int get_next_line(const int fd, char **line)
{
	int nb;
	char buf[BUFF_SIZE + 1];
	static char *inputcont[1];
	char *tmp;

	if (fd < 0 || line == NULL ||(read(fd, buf, 0) < 0))
		return (-1);
	while ((nb = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!inputcont[fd])
			inputcont[fd] = ft_strnew(1);
		buf[nb] = '\0';
		tmp = ft_strjoin(inputcont[fd], buf);
		free(inputcont[fd]);
		inputcont[fd] = tmp;
		tmp = NULL;
		if (ft_strchr(buf, '\n') != NULL)
			break ;
	}
	if (nb == 0 && inputcont[fd] == NULL)
		return (-1);
	if (*inputcont[fd] == '\0') //
		return (0);
	*line = find_line(&inputcont[fd]);
	return (1);
}

void clean_env(char ***env_cp)
{
	int len;
	int j;

	j = 0;

	len = str_quantity();
	while (j < len)
	{
		ft_memdel((void**)&(g_env[j]));
		j++;
	}
	free(*env_cp);
	*env_cp = NULL;
}

char	*path(char *name, char *path)
{
	char	*full;
	char	*tmp;

	if (path[ft_strlen(path) - 1] == '/')
		return (ft_strjoin(path, name));
	else
	{
		tmp = ft_strjoin(path, "/");
		full = ft_strjoin(tmp, name);
		ft_memdel((void **)&tmp);
	}
	return (full);
}

int builtin(char **args)
{
  if (ft_strcmp(args[0], "cd") == 0)
    return (cd_cmnd(args));
  if (ft_strcmp(args[0], "env") == 0)
    return (env_cmnd());
  if (ft_strcmp(args[0], "setenv") == 0)
  	return(setenv_cmnd(args[1], args[2]));
  if (ft_strcmp(args[0], "unsetenv") == 0)
    return (unsetenv_cmnd(args[1]));
  if (ft_strcmp(args[0], "echo") == 0)
    return (echo_cmnd(args));
  if (ft_strcmp(args[0], "exit") == 0)
    return (exit_cmnd());
  return (1);
}

int launch(char *file, char **args)
{
	pid_t pid;
	int status;

	pid = fork(); // make copy of process (child)
	if (pid == 0) // child process
	{
		if (execve(file, args, g_env) == -1) //replace current running process with new one
			perror_cmnd("minishell", NULL, EXECVEERR);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) // fork error
		perror_cmnd("minishell", NULL, FORKERR);
	else // parent process
	{
		waitpid(pid, &status, WUNTRACED); // приомтанавливает родительский процесс (PID процесса), пока дочерний процесс не завершится или до появления сигнала
		while (!WIFEXITED(status) && !WIFSIGNALED(status)) //макросы: WIFEXITED != 0, если дочерний процесс завершен, WIFSIGNALED - ывозвращет истинное значение,если дочерний процесс завершился из-за необработанного сигнала
			waitpid(pid, &status, WUNTRACED);
	}
	return (1); //continue to execute
}

int		find_bin(char *cmnd_name, char *path)
{
	DIR				*dir;
	struct dirent	*dir_ptr;

	if ((dir = opendir(path)))
    {
        while ((dir_ptr = readdir(dir)))
            if (ft_strcmp(dir_ptr->d_name, cmnd_name) == 0)
            {
                closedir(dir);
                return (1);
            }
    }
    closedir(dir);
	return (0);
}

int external_launch(char **cmnd, char *paths)
{
	char *filepath;
    
    if (!access(cmnd[0], R_OK)) // check //X_OK??
    {
        perror_cmnd("minishell", cmnd[0], 0);
        return (1);
    }
	filepath = path(cmnd[0], paths);
	return (launch(filepath, cmnd));
}

int		check_builtin(char *cmnd)
{
	if (ft_strcmp(cmnd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmnd, "env") == 0)
		return (1);
	if (ft_strcmp(cmnd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmnd, "setenv") == 0)
		return (1);
	if (ft_strcmp(cmnd, "unsetenv") == 0)
		return (1);
	if (ft_strcmp(cmnd, "exit") == 0)
		return (1);
	return (0);
}

int		absolute_path_launch(char **cmnd)
{
	if (access(cmnd[0], X_OK))
	{
        if (access(cmnd[0], F_OK) == -1)
            perror_cmnd("minishell", cmnd[0], CMNDNTFND);
        else
            perror_cmnd("minishell", cmnd[0], PMDND);
        return(1);
	}
	return (launch(cmnd[0], cmnd));
}

char		*check_extern_command(char **cmnd)
{
	char	*env_path;
	char	**paths;
	int		i;
	int paths_quant;

	i = 0;
	paths_quant = 0;
//    env_path = getenv_cmnd("PATH");
    if (!(env_path = getenv_cmnd("PATH")))//ok
        return (NULL);
	paths = ft_strsplit(env_path, ':'); // invalid read->count words
	while (paths[paths_quant])
		paths_quant++;
	while (i < paths_quant) //seg
	{
		if ((find_bin(cmnd[0], paths[i])))
			return (paths[i]);
		i++;
	}
return (NULL);
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

void handler_interrupt(int signal)
{
	if (signal == SIGINT)
	{
        ft_putchar_fd('\n', STDIN_FILENO);
		return ;
	}
}
void	signals()
{
	signal(SIGINT, handler_interrupt);
}

void cmnd_loop()
{
	char *line;
	char **args;
	int status;
	int flag;
	int i;

	args = NULL;
	status = 1;
	while (status)
	{
		flag = 0;
//        ft_putstr(SHELL_NAME);
//    if ((get_next_line(STDIN_FILENO, &line)))
        if ((line = readline(SHELL_NAME)))
		{
            signals();
			// READ
			if ((strrchr(line, ';'))) {
				flag = 1;
				if (!(args = ft_strsplit(line, ';')))
					perror_cmnd("minishell", NULL, MLKERR);
			}
			if (flag)
			{
				i = 0;
				while (args[i])
				{
					status = execute_cmnd(split_cmnd(args[i], ' '));
					if (status == 0)
						continue;
					i++;
				}
			}
			else
				{
				args = split_cmnd(line, ' ');
				status = execute_cmnd(args);
				free(args);
			}
            add_history(line);
			free(line);
		}
	else
            return ;

	}
}


int main(int argc, char **argv, char **env)
{
	char **env_cp;

	env_cp = NULL;
	argv = NULL;
	if (argc == 1)
	{
	 env_cp = make_env_cp(env_cp, env);
	 g_env = env_cp;
	 cmnd_loop();
	///	// exit, cleanup
	}
	else
		print_usage();
	return (0);
}

