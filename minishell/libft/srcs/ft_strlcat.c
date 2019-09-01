/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:35:08 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/03 19:02:20 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t len_dst;
	size_t len_src;

	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen (src);
	if (size  <= len_dst)
		return(len_src + size);
	while (len_dst + i < size - 1)
		{
			dst[len_dst + i] = src[i];
			i++;
		}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
