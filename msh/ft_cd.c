/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:23:10 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/03 16:47:30 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_pwd(char **envp, char *name)
{
	char **parse;

	parse = (char **)malloc(sizeof(char *) * 4);
	parse[0] = ft_strdup("setenv");
	parse[1] = ft_strdup("PWD");
	parse[2] = ft_strdup(name);
	parse[3] = NULL;
	envp = ft_setenv(parse, envp);
	free_parse(parse, 3);
	return (envp);
}

char	**ft_cd_stuf(char **parse, char **envp)
{
	int		res;
	char	buf[2048];

	res = chdir(parse[1]);
	if (res == -1)
	{
		if (access(parse[1], F_OK) == 0)
		{
			ft_putstr("cd: permission denied: ");
			ft_putendl(parse[1]);
		}
		else
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(parse[1]);
		}
	}
	if (res == 0)
		envp = update_pwd(envp, getcwd(buf, 2048));
	return (envp);
}

char	**ft_cd(char **parse, char **envp)
{
	int		i;
	char	*home;

	home = ft_getenv("HOME", envp);
	i = 0;
	while (parse[i])
		i++;
	if (i > 2)
	{
		ft_putendl("cd: too many arguments");
		return (envp);
	}
	--i;
	if (i == 0)
	{
		if (home != NULL)
			if (chdir(home) == 0)
				envp = update_pwd(envp, home);
	}
	if (i == 1)
		envp = ft_cd_stuf(parse, envp);
	return (envp);
}
