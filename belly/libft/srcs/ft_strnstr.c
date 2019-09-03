/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:48:45 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/03 15:52:55 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
   size_t little_len;
 
	if (*needle == '\0')
	  return ((char *)haystack);
	
	little_len = ft_strlen(needle);
	while (*haystack != '\0' && little_len <= len--)
	  {
	    if (*haystack == *needle && ft_strncmp(haystack, needle, little_len) == 0)
	      return ((char *)haystack);
	    haystack++;
	  }
	  return (NULL);
}
