
#include "../includes/minishell.h"

void rewrite_env(int index)
{
	char	**env;
	short	i;
	int str_quan;

	str_quan = str_quantity();
	if (!(env = (char**)malloc(sizeof(char *) * str_quan)))
		perror_cmnd("unsetenv", NULL, MLKERR);
	i = 0;
	while (g_env[i] && g_env[i + 1])
	{
		if (i < index)
			env[i] = g_env[i];
		else
		{
			if (i == index)
				ft_memdel((void**)&(g_env[i]));
			env[i] = g_env[i + 1];
		}
		i++;
	}
	env[str_quan] = NULL;
	free(g_env);
	g_env = env;
}

//int unsetenv_cmnd(char *name) //need to finish
//{
//	int index;
//
//	if (!name)
//	{
//		ft_putstr("usage: unsetenv [name]");
//		return (1);
//	}
//	if (g_env)
//	{
//		if ((index = get_envindex(name)) == -1)
//			return (1);
//		rewrite_env(index);
//	}
//	return (1); // continue to execute
//}








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

    index = get_envindex(name);
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

int		count_pointers(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    return (i);
}
void	free_parse(char **parse, int w)
{
    int i;

    i = 0;
    w++;
    while (i < w)
    {
        free(parse[i]);
        i++;
    }
    free(parse);
}
void	free_copy_envp(char ***envp)
{
    int		p;
    char	**ref;

    ref = *envp;
    p = count_pointers(ref);
    free_parse(ref, p);
//    envp = NULL;
}
int unsetenv_cmnd(char *name)
{
    char	**new_env;
    int		p;

    if (!name)
    {
        ft_putstr("usage: unsetenv [name]");
        return (1); //
    }
//    new_env = NULL;
        if (getenv_cmnd(name) != NULL)
        {
            p = str_quantity() - 1;
            new_env = realloc_envp_del(p, name, g_env);
            free_copy_envp(&g_env);
            g_env = new_env;
        }

    return (1);
}