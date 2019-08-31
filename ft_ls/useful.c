/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <bellyn-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 21:12:31 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/08/31 14:09:49 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		nbtostr(long int n, int i, char *buf)
{
	if (n > 9)
		nbtostr(n / 10, i - 1, buf);
	buf[i] = n % 10 + '0';
}

uint16_t	get_sizelen(int num)
{
	uint16_t	len;

	len = 1;
	if (!num)
		return (len);
	while (num /= 10)
		len++;
	return (len);
}

void		skip_word(char *res, struct s_word *str)
{
	while (res[str->j] != ':')
		str->j++;
}

void		draw_word(char *res, char *buf, struct s_word *str)
{
	while (res[++(str->j)] != ':')
		buf[(str->i)++] = res[str->j];
}

int			draw_zero(char *buf)
{
	char	*zero;
	int		i;
	int		j;

	i = 0;
	j = 0;
	zero = " 0: ";
	while (zero[j])
		buf[i++] = zero[j++];
	return (i);
}
