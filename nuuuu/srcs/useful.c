#include "ft_ls.h"

void	nbtostr(long int n, int i, char *buf)
{
	if (n > 9)
		nbtostr(n / 10, i - 1, buf);
	buf[i] = n % 10 + '0';
}

uint16_t get_sizelen(int num)
{
	uint16_t	len;

	len = 1;
	if (!num)
		return (len);
	while (num /= 10)
		len++;
	return (len);
}