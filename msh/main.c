/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:47:55 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/01 17:01:51 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_dir(char *path_from_env, char *name)
{
	DIR				*dir;
	struct dirent	*d;

	dir = opendir(path_from_env);
	if (dir != NULL)
	{
		while ((d = readdir(dir)) != NULL)
		{
			if (ft_strcmp(d->d_name, name) == 0)
			{
				closedir(dir);
				return (1);
			}
		}
		closedir(dir);
	}
	return (0);
}

int		check_path(char *path)
{
	if (access(path, X_OK) == -1)
	{
		ft_putstr("minishell: permission denied: ");
		ft_putendl(path);
		return (-1);
	}
	return (0);
}

void	handle_sig(int sig)
{
	if (sig == 2)
		return ;
}

char	**action(char *cmd, char **my_env)
{
	int		i;
	int		count;
	char	**parsed_cmd;

	i = 0;
	count = count_words_delim(cmd, ';');
	parsed_cmd = ft_split_delim(cmd, count, ';');
	while (i < count)
	{
		my_env = take_command(parsed_cmd[i], my_env);
		i++;
	}
	free_parse(parsed_cmd, count);
	return (my_env);
}

int		main(int argc, char **argv, char **envp)
{
	char		*cmd;
	static char **my_env;

	(void)argv;
	cmd = NULL;
	if (argc == 1)
	{
		my_env = create_env_copy(envp, count_pointers(envp));
		while (my_env != NULL)
		{
			signals();
			cmd = readline("♿  \e[96m\e[1mminishell \e[0m");
			if (cmd == NULL || !cmd)
			{
				ft_exit(my_env);
				break ;
			}
			add_history(cmd);
			my_env = action(cmd, my_env);
			free(cmd);
		}
	}
	return (0);
}
