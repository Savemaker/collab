#include "minishell.h"

int     env_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

char	**split(char **str, char *s, char c, int count)
{
    int i;
    int start;
    int n_mas;
    char *val;

    i = 0;
    n_mas = 0;
    while (s[i] != '\0' && n_mas < count) {
        if (s[i] != c && s[i] != '\t' && s[i] != '\r' && s[i] != '\v' && s[i] != '"')
        {
            start = i;
            while (s[i] != '\0' && s[i] != c && s[i] != '"')
                i++;
            if (s[start] == '~')
                str[n_mas] = ft_strjoin(getenv("HOME"), &s[start] + 1);
            else if (s[start] == '$' && env_strlen(&s[start]) == 1)
                str[n_mas] = ft_strdup("$");
            else if (s[start] == '$' && (val = getenv_cmnd(ft_strsub(s, start + 1, env_strlen(&s[start + 1])))))
                str[n_mas] = ft_strdup(val);
            else if (s[start] == '$' && !val)
                str[n_mas] = ft_strdup(" ");
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

int		count_words(char *str, char sign)
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
