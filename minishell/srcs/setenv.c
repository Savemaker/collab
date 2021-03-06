//
// Created by Екатерина on 2019-08-20.
//
#include "../includes/minishell.h"

int		check_existenv(const char *name, char *request)
{
	size_t len;

	len = 0;
	while (request[len] && request[len] != '=')
		len++;
	if (ft_strlen(name) != len)
		return (0);
	return (1);
}

int		get_envindex(const char *name)
{
	int		i;
	char	*request;

	i = 0;
	while (g_env[i])
	{
		if ((request = ft_strstr(g_env[i], name)))
			if ((check_existenv(name, request)))
				return (i);
		i++;
	}
	return (-1);
}

int checkenv(char *envstr)
{
	if (!(ft_strchr(envstr, '=')))
	{
		perror_cmnd("minishell", NULL, SETENVERR);
		return (0);
	}
	return (1);
}

char	*getenv_cmnd(char *name)
{
	int		i;
	char	*request;

	i = 0;
	while (g_env[i])
	{
		if ((checkenv(g_env[i])))
			if ((request = ft_strstr(g_env[i], name)))
				if ((check_existenv(name, request)))
					return (request + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}

int		str_quantity()
{
	int i;

	i = 0;
	while (g_env[i])
		i++;
	return (i);
}

char *joinenv(char *name, char *value)
{
	char *tmp1;
	char *tmp2;

	if (!(tmp1 = ft_strjoin(name, "=")))
		perror_cmnd("minishell", NULL, MLKERR); //malloc()
	if (!(tmp2 = ft_strjoin(tmp1, value)))
		perror_cmnd("minishell", NULL, MLKERR); // malloc()
	ft_memdel((void **)&tmp1);
	return(tmp2);
}

//int setenv_cmnd(char *name, char *value)
//{
//	char	**newenv;
//	int		str_quan;
//	int index;
//
//	if (!name || !value)
//	{
//		ft_putstr("usage: setenv [name] [value]\n"); //not enough arguments
//		return (1);
//	}
//	if ((index = get_envindex(name)) != -1)
//		g_env[index] = joinenv(name, value);
//	else
//		{
//		str_quan = str_quantity();
//		if (!(newenv = (char **)malloc(sizeof(char *) * (str_quan + 2))))
//			perror_cmnd("minishell", NULL, MLKERR);
//		index = 0;
//		while (index < str_quan)
//		{
//			newenv[index] = g_env[index];
//			index++;
//		}
//		newenv[index] = joinenv(name, value);
//		newenv[++index] = NULL;
////		clean_env(&g_env);
//		free(g_env);
//		g_env = newenv;
//	}
//	return (1);
//}

void	copy_index(char **ress, char *name, char *value)
{
    int		i;
    int		j;
    char	*res;

    res = *ress;
    i = 0;
    j = 0;
    while (name[i])
    {
        res[i] = name[i];
        i++;
    }
    res[i++] = '=';
    j = 0;
    while (value[j])
    {
        res[i] = value[j];
        i++;
        j++;
    }
    res[i] = '\0';
}

void	copy_to_realloc(char **envp, char **res, char *name, char *value)
{
    int index;
    int i;
    int j;

    index = get_envindex(name);
    i = 0;
    j = 0;
    while (envp[i])
    {
        j = 0;
        if (index != i)
        {
            while (envp[i][j] != '\0')
            {
                res[i][j] = envp[i][j];
                j++;
            }
            res[i][j] = '\0';
        }
        if (index == i)
            copy_index(&res[i], name, value);
        i++;
    }
    if (index == -1)
        copy_index(&res[i], name, value);
}

char	*malloc_line(char *name, char *value)
{
    char	*res;
    int		name_len;
    int		value_len;

    name_len = ft_strlen(name);
    value_len = ft_strlen(value);
    res = (char *)malloc(sizeof(char) * (name_len + value_len + 2));
    if (res == NULL)
        return (NULL);
    return (res);
}

char	**realloc_envp(int pointers, char *name, char *value, char **envp)
{
    char	**res;
    int		index;
    int		i;

    i = 0;
    res = (char **)malloc(sizeof(char *) * (pointers + 1));
    index = get_envindex(name);
    if (index == -1)
        --pointers;
    while (i < pointers)
    {
        if (i == index)
            res[i] = malloc_line(name, value);
        else
            res[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
        i++;
    }
    if (index == -1)
        res[i++] = malloc_line(name, value);
    res[i] = NULL;
    copy_to_realloc(envp, res, name, value);
    return (res);
}


int setenv_cmnd(char *name, char *value)
{
    char	**new_env;
    int		p;

    if (!name || !value)
    {
        ft_putstr("usage: setenv [name] [value]\n"); //not enough arguments
        return (1);
    }
    else
    {
        p = str_quantity();
        if (getenv_cmnd(name) == NULL)
            p++;
        new_env = realloc_envp(p, name, value, g_env);
        free_copy_envp(&g_env);
        g_env = new_env;
    }
    return (1);
}