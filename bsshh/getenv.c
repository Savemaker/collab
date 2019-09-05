#include "minishell.h"


int		str_quantity(char **env) //поменять
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

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