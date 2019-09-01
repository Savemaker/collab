/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:32:06 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/01 16:37:53 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_realloc_del(char **res, char **envp, int index)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (envp[i])
	{
		if (i == index)
		{
			i++;
			continue;
		}
		j = 0;
		while (envp[i][j])
		{
			res[k][j] = envp[i][j];
			j++;
		}
		res[k][j] = '\0';
		k++;
		i++;
	}
}

char	**realloc_envp_del(int p, char *name, char **envp)
{
	int		i;
	int		j;
	char	**res;
	int		index;

	index = ft_getenv_index(name, envp);
	i = 0;
	j = 0;
	res = (char **)malloc(sizeof(char *) * (p + 1));
	while (i < p)
	{
		if (index == j)
			j++;
		res[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[j]) + 1));
		j++;
		i++;
	}
	res[i] = NULL;
	copy_realloc_del(res, envp, index);
	return (res);
}

char	**ft_unsetenv(char **parse, char **envp)
{
	char	**new_env;
	int		p;

	new_env = NULL;
	if (parse[1] != NULL)
	{
		if (ft_getenv(parse[1], envp) != NULL)
		{
			p = count_pointers(envp) - 1;
			new_env = realloc_envp_del(p, parse[1], envp);
			free_copy_envp(&envp);
		}
	}
	return (new_env);
}

void	signals(void)
{
	signal(SIGINT, handle_sig);
}

void	ft_cd_stuf(char **parse, int i)
{
	int res;

	res = chdir(parse[i]);
	if (res == -1)
	{
		if (access(parse[i], F_OK) == 0)
		{
			ft_putstr("cd: permission denied: ");
			ft_putendl(parse[i]);
		}
		else
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(parse[i]);
		}
	}
}
