/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:45:23 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/03 19:40:51 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_base(int copy_n)
{
	int base;

	base = 0;
	if (copy_n < 0)
	{
		copy_n *= -1;
		base++;
	}
	while (copy_n > 0)
	{
		copy_n /= 10;
		base++;
	}
	return (base);
}

char		*ft_itoa(int n)
{
	char	*num;
	int		base;

	base = ft_base(n);
	if (!(num = (char *)malloc(sizeof(char) * base + 1)))
	  return (NULL);
	if (n == -2147483648)
	  return (ft_strcpy(num, "-2147483648"));
	num[base--] = '\0';
	if (n == 0)
	{
		num[0] = '0';
		return (num);
	}
	if (n < 0)
	{
		num[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		num[base] = '0' + n % 10;
		n /= 10;
		base--;
	}
	return (num);
}
