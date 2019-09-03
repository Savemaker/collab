/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:36:00 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/11/30 13:37:13 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*newsub;

	i = 0;
	if (!s || !len || s[start] == '\0')
		return (NULL);
	if (!(newsub = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len && s[start])
	{
		newsub[i] = (char)s[start];
		i++;
		start++;
	}
	newsub[i] = '\0';
	return (newsub);
}
