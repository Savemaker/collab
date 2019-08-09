#include "ft_ls.h"

void	usage_msg(char c) // add new
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ls [-GRSadfglrtu] [file ...]\n");
	exit(-1);
}

uint16_t	define_flag(uint16_t allflags, char receivedflag) //larRtufgdG
{
	if (receivedflag == 'l') //выдавать в одноколоночном формате тип файла, права доступа, количестов ссылок на файл, имя владельца, имя группы, размер файла в байтах, временной штамп и имя
		return (SET_BIT(allflags, 0));
	if (receivedflag == 'a') //показывать скрытые файлы
		return (SET_BIT(allflags, 1));
	if (receivedflag == 'r') //обратная сортировка
		return (SET_BIT(allflags, 2));
	if (receivedflag == 'R') //ресурсивно ототбражать содердимое директорий
		return (SET_BIT(allflags, 3));
	if (receivedflag == 't') //сортировка по временному штампу
		return (SET_BIT(allflags, 4));
	if (receivedflag == 'u') //использовать при -t или -l время последнего доступа к файлу (а не последнюю модификацию)
		return (SET_BIT(allflags, 5));
	if (receivedflag == 'f') //не сортировать
		return (SET_BIT(allflags, 6));
	if (receivedflag == 'g') //показывть подробную инфу, кроме владельца
		return (SET_BIT(allflags, 7));
	if (receivedflag == 'd') //выводить только названия директорий
		return (SET_BIT(allflags, 8));
	if (receivedflag == 'G') //не выводить имена групп
		return (SET_BIT(allflags, 9));
	if (receivedflag == 1)	 //выдавать в одноколоночном формате
		return (SET_BIT(allflags, 10));
	if (receivedflag == '@') //доп атрибуты
		return (SET_BIT(allflags, 11));
	if (receivedflag == 'S') //сорт по размеру, от большего
		return (SET_BIT(allflags, 12));
	if (receivedflag == 'e')
		return (SET_BIT(allflags, 13));
	usage_msg(receivedflag);
	return (0);
}

uint16_t	add_flags(char **argv, uint16_t *flags_q)
{
	uint16_t j;
	uint16_t flags;

	flags = 0;
	*flags_q = 1; //потому что с 1 аргв начинаем, ниже вычтем
	while (argv[*flags_q] && argv[*flags_q][0] == '-' && ft_strlen(argv[*flags_q]) != 1) //парсинг
	{
		j = 1;
		while (argv[*flags_q][j])
		{
			flags = define_flag(flags, argv[*flags_q][j]);
			j++;
		}
		(*flags_q)++;
	}
	(*flags_q)--;
	return (flags);
}

uint16_t	check_flags(uint16_t flags, char flag)
{
	if (flag == 'l' && CHECK_FLAG(flags, 0) == BIT(0))
		return (1);
	if (flag == 'a' && CHECK_FLAG(flags, 1) == BIT(1))
		return (1);
	if (flag == 'r' && CHECK_FLAG(flags, 2) == BIT(2))
		return (1);
	if (flag == 'R' && CHECK_FLAG(flags, 3) == BIT(3))
		return (1);
	if (flag == 't' && CHECK_FLAG(flags, 4) == BIT(4))
		return (1);
	if (flag == 'u' && CHECK_FLAG(flags, 5) == BIT(5))
		return (1);
	if (flag == 'f' && CHECK_FLAG(flags, 6) == BIT(6))
		return (1);
	if (flag == 'g' && CHECK_FLAG(flags, 7) == BIT(7))
		return (1);
	if (flag == 'd' && CHECK_FLAG(flags, 8) == BIT(8))
		return (1);
	if (flag == 'G' && CHECK_FLAG(flags, 9) == BIT(9))
		return (1);
	if (flag == 1 && CHECK_FLAG(flags, 10) == BIT(10))
		return (1);
	if (flag == '@' && CHECK_FLAG(flags, 11) == BIT(11))
		return (1);
	if (flag == 'S' && CHECK_FLAG(flags, 12) == BIT(12))
		return (1);
	if (flag == 'e' && CHECK_FLAG(flags, 13) == BIT(13))
		return (1);
	return (0);
}