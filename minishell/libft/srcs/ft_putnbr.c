/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:34:22 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/11/30 18:25:09 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
  if (n == -2147483648)
    ft_putstr("-2147483648");
  else if (n < 0)
    {
      ft_putchar('-');
      ft_putnbr(n *= -1);
    }
  else if (n > 9)
    {
      ft_putnbr(n / 10);
      ft_putchar((n % 10) + '0');
    }
  else 
    ft_putchar(n + '0');
}
