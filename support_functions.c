#include "ft_printf.h"


void	buff_filler(t_print_params *pr_par, int sym)
{
	pr_par->printf_buf[pr_par->buff_cntr] = sym;
	pr_par->buff_cntr++;
}
/*
char	*exceptions(char *str, long long n)
{
	//if (n == 4294967295)
	//	return ("4294967295");
	//if (n == 4294967296)
	//	return ("0");
	//else if (n == -9223372036854775808)
	//	return ("-9223372036854775808");
	//else
		return (str);
}*/
char	*ft_itoa_option(char *str, t_print_params *pr_par, int sign, long long n)
{
	//str = exceptions(str, n);
	//printf("\n\nitoa_option0: %s\n\n", str);
	if (pr_par->prec_indic == 1 && pr_par->precision == 0 && n == 0)
		str = "";
	while ((int)ft_strlen(str) < pr_par->precision)
		str = ft_strjoin("0", str);
	//printf("\n\nitoa_option2: %s\n\n", str);
	if (pr_par->use_zeros == 1 && pr_par->align_to_left != 1)
	{
		while ((int)ft_strlen(str) < pr_par->padding_size - 1
		- 1 * ((pr_par->alt_format == 1 && n != 0)))
			str = ft_strjoin("0", str);
	}
	//printf("\n\nitoa_option3: %s\n\n", str);
	if (pr_par->alt_format == 1 && n != 0)
	{
		if (pr_par->type == 'x')
			str = ft_strjoin("0x", str);
		else if (pr_par->type == 'X')
			str = ft_strjoin("0X", str);
		else if (pr_par->type == 'o')
			str = ft_strjoin("0", str);
	}
	if (pr_par->alt_format == 1 && n == 0 && pr_par->type == 'o')
		return("0");
	if (sign < 0)
		str = ft_strjoin("-", str);
	else if (pr_par->space_option == 1  &&
	pr_par->print_sign == 0 && sign > 0 && pr_par->type != 'u')
		str = ft_strjoin(" ", str);
	else if (pr_par->print_sign == 1 && sign > 0 && pr_par->type != 'u')
		str = ft_strjoin("+", str);
	//printf("\n\nitoa_option: %s\n\n", str);
	return (str);
}

char	*ft_itoa_base(long long n, int base, t_print_params *pr_par)
{
	long long	ch;
	char		*str;
	int			cnt;
	int			sign;

	if (n < 0 && base != 10)
		n = n + pow(2, 32);
	sign = (n < 0) ? -1 : 1;
	cnt = 1;//(n < 0) ? 2 : 1;
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
	('0' + (ch % base)) : (pr_par->hex_sym + (ch % base - 10));
		ch /= base;
	}
	//printf("\n\nn: %lld\nstr: %s", n, str);
	return (ft_itoa_option(str, pr_par, sign, n));
}



/*
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
	return (ft_itoa_option(str, option, sign));
}*/