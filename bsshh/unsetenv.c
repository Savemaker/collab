#include "minishell.h"

void	copy_realloc_del(char **res, char **env, int index)
{
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    while (env[i])
    {
        if (i == index)
        {
            i++;
            continue;
        }
        j = 0;
        while (env[i][j])
        {
            res[k][j] = env[i][j];
            j++;
        }
        res[k][j] = '\0';
        k++;
        i++;
    }
}

char	**realloc_envp_del(int p, char *name, char **env)
{
    int		i;
    int		j;
    char	**res;
    int		index;

    index = get_envindex(name);
    i = 0;
    j = 0;
    if (!(res = (char**)malloc(sizeof(char *) * p + 1)))
        perror_cmnd("unsetenv", NULL, MLKERR);
    while (i < p)
    {
        if (index == j)
            j++;
       if (!(res[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1))))
           perror_cmnd("unsetenv", NULL, MLKERR);
        j++;
        i++;
    }
    res[p] = NULL;
    copy_realloc_del(res, env, index);
    return (res);
}

int unsetenv_cmnd(char *name)
{
    char	**new_env;

    if (!name)
    {
        ft_putstr("usage: unsetenv [name]\n");
        return (1);
    }
        if (getenv_cmnd(name) != NULL)
        {
            new_env = realloc_envp_del(str_quantity(g_env) - 1, name, g_env);
            free_copy_envp(&g_env);
            g_env = new_env;
        }

    return (1);
}
