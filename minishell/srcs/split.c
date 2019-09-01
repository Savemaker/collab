//
// Created by Екатерина on 2019-08-20.
//

#include "../includes/minishell.h"

static	char	**split(char **str, char *s, char c, int count)
{
	int i;
	int start;
	int n_mas;

	i = 0;
	n_mas = 0;
	while (s[i] != '\0' && n_mas < count)
	{
		if (s[i] != c && s[i] != '\t' && s[i] != '\r' && s[i] != '\v')
		{
			start = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			if (s[start] == '$')
			{
				str[n_mas] = ft_strdup(getenv(ft_strsub(s, start + 1, i - start)));
			}
			else
				str[n_mas] = ft_strsub(s, start, i - start);
			n_mas++;
		}
		else
			i++;
	}
	str[n_mas] = NULL;
	return (str);
}

static	int		count_words(char *str, char sign)
{
	int i;
	int i_of_word;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		i_of_word = 0;
		while (str[i] != sign && str[i] != '\0')
		{
			i_of_word++;
			i++;
		}
		if (i_of_word != 0)
			count++;
		i++;
	}
	return (count);
}

char			**split_cmnd(char const *s, char c)
{
	char **str;
	char count;

	if (s)
	{
		count = count_words((char *)s, c);
		if (!(str = (char **)malloc(sizeof(char *) * (count + 1))))
			return (NULL);
		str = split(str, (char *)s, c, count);
		return (str);
	}
	return (NULL);
}
