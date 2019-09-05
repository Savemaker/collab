#include "minishell.h"

void	join_env(char **ress, char *name, char *value)
{
    char	*tmp;

    
    if (!(tmp = ft_strjoin(name, "=")))
        perror_cmnd("minishell", NULL, MLKERR);
    if (!(*ress = ft_strjoin(tmp, value)))
        perror_cmnd("minishell", NULL, MLKERR);
    ft_memdel((void **)&tmp);
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
            join_env(&res[i], name, value);
        i++;
    }
    if (index == -1)
        join_env(&res[i], name, value);
}

char	*malloc_line(char *name, char *value)
{
    char	*res;

    if (!(res = (char *)malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2))))
    {
        perror_cmnd("setenv", NULL, MLKERR);
        return (NULL);
    }
    return (res);
}

char	**realloc_envp(int pointers, char *name, char *value, char **env)
{
    char	**res;
    int		index;
    int		i;

    i = 0;
    res = (char **)malloc(sizeof(char *) * (pointers + 1));
    if ((index= get_envindex(name)) == -1)
        --pointers;
    while (i < pointers)
    {
        if (i == index)
            res[i] = malloc_line(name, value);
        else
            if (!(res[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1))))
                perror_cmnd("setenv", NULL, MLKERR);
        i++;
    }
    if (index == -1)
        res[i++] = malloc_line(name, value);
    res[i] = NULL;
    copy_to_realloc(env, res, name, value);
    return (res);
}

int setenv_cmnd(char *name, char *value)
{
    char	**new_env;
    int		p;

    if (!name || !value)
    {
        ft_putstr("usage: setenv [name] [value]\n");
        return (1);
    }
    else
    {
        p = str_quantity(g_env);
        if (getenv_cmnd(name) == NULL)
            p++;
        new_env = realloc_envp(p, name, value, g_env); //clean
        clean_env(g_env);
        g_env = new_env;
    }
    return (1);
}
