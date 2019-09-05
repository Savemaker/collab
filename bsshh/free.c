#include "minishell.h"

void clean_env(char **env_cp)
{
	int len;
	int j;

	j = 0;

	len = str_quantity(env_cp);
	while (j <= len)
	{
		ft_memdel((void**)&(env_cp[j]));
		j++;
	}
	free(env_cp);
	env_cp = NULL;
}

void	free_parse(char **parse, int w)
{
	int i;

	i = 0;
	while (i < w)
	{
		free(parse[i]);
		i++;
	}
	free(parse);
}

void	free_copy_envp(char ***envp)
{
	char	**ref;

	ref = *envp;
	free_parse(ref, str_quantity(ref) + 1);
}