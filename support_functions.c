#include "ft_printf.h"


void	buff_filler(t_print_params *pr_par, int sym)
{
	pr_par->printf_buf[pr_par->buff_cntr] = sym;
	pr_par->buff_cntr++;
}

char	*ft_itoa_option(char *str, char option, int sign)
{
	if (sign < 0)
		str[0] = '-';
	else if (option == ' ' && sign > 0)
		str[0] = ' ';
	else if (option == '+' && sign > 0)
		str[0] = '+';
	return (str);
}

char	*ft_itoa_base(long long n, int base, char option, char x)
{
	long long	ch;
	char		*str;
	int			cnt;
	int			sign;

	sign = (n < 0) ? -1 : 1;
	cnt = (n < 0 || option != '0') ? 2 : 1;
	ch = n;
	ch *= sign;
	while (ch /= base)
		cnt++;
	str = ft_strnew(cnt);
	if (!str)
		return (NULL);
	str[0] = '0';
	ch = n;
	ch *= sign;
	while (ch > 0)
	{
		str[--cnt] = (ch % base) < 10 ?
	('0' + (ch % base)) : (x + (ch % base - 10));
		ch /= base;
	}
	//if (sign == -1 || option == 1)
	//	str[0] = '-';
	//return (str);
	return (ft_itoa_option(str, option, sign));
}