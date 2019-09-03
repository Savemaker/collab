/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:40:26 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/03 18:23:22 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"



static	char	**ft_split(char **str, char *s, char c, int count)
{
	int i;
	int start;
	int n_mas;

	i = 0;
	n_mas = 0;
	while (s[i] != '\0' && n_mas < count)
	{
		if (s[i] != c && !ft_isspace(s[i]))
		{
			start = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			str[n_mas] = ft_strsub(s, start, i - start);
			n_mas++;
		}
		else
			i++;
	}
	str[n_mas] = NULL;
	return (str);
}

static	int		ft_count_words(char *str, char sign)
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

char			**ft_strsplit(char const *s, char c)
{
	char **str;
	char count;

	if (s)
	{
		count = ft_count_words((char *)s, c);
		if (!(str = (char **)malloc(sizeof(char *) * (count + 1))))
			return (NULL);
		str = ft_split(str, (char *)s, c, count);
		return (str);
	}
	return (NULL);
}
