#include "ft_printf.h"

void	buff_filler(t_print_params *pr_par, int sym)
{
	pr_par->printf_buf[pr_par->buff_cntr] = sym;
	pr_par->buff_cntr++;
}

char	*itoa_option_help(char *str, t_print_params *pr_par, int is_zero)
{
	if (pr_par->prec_indic == 1 &&
	pr_par->precision == 0 && is_zero == 1)
		str = ft_strjoin_free("", "", 0);
	while ((int)ft_strlen(str) < pr_par->precision -
	(pr_par->type == 'f' ? pr_par->precision + 1 : 0))
		str = ft_strjoin_free("0", str, 2);
	if (pr_par->use_zeros == 1 && pr_par->align_to_left != 1)
	{
		while ((int)ft_strlen(str) < pr_par->padding_size - 1
		- (pr_par->type == 'f' ? pr_par->precision + 1 : 0)
		- 1 * ((pr_par->alt_format == 1 && is_zero == 0)))
			str = ft_strjoin_free("0", str, 2);
	}
	if (pr_par->alt_format == 1 && is_zero == 0)
	{
		if (pr_par->type == 'x')
			str = ft_strjoin_free("0x", str, 2);
		else if (pr_par->type == 'X')
			str = ft_strjoin_free("0X", str, 2);
		else if (pr_par->type == 'o' && pr_par->precision == 0)
			str = ft_strjoin_free("0", str, 2);
	}
	return (str);
}

char	*ft_itoa_option(char *str, t_print_params *pr_par,
	int sign, int is_zero)
{
	str = itoa_option_help(str, pr_par, is_zero);
	if (pr_par->alt_format == 1 && is_zero == 1
	&& pr_par->type == 'o')
		return (ft_strjoin_free("0", "", 0));
	if (sign < 0)
		str = ft_strjoin_free("-", str, 2);
	else if (pr_par->space_option == 1 &&
	pr_par->print_sign == 0 && sign > 0 && pr_par->type != 'u')
		str = ft_strjoin_free(" ", str, 2);
	else if (pr_par->print_sign == 1 && sign > 0 && pr_par->type != 'u')
		str = ft_strjoin_free("+", str, 2);
	return (str);
}

char	*ft_itoa_base(long long n, int base, t_print_params *pr_par)
{
	long long	ch;
	char		*str;
	int			cnt;
	int			sign;

	if (n < 0 && base != 10)
		n = n + 4294967296;
	sign = (n < 0) ? -1 : 1;
	cnt = 1;
	ch = n * sign;
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
	return (ft_itoa_option(str, pr_par, sign, (n == 0) ? 1 : 0));
}

char	*ft_itoa_base_uns(unsigned long long n,
	int base, t_print_params *pr_par)
{
	unsigned long long	ch;
	char				*str;
	int					cnt;

	cnt = 1;
	ch = n;
	while (ch /= base)
		cnt++;
	str = ft_strnew(cnt);
	if (!str)
		return (NULL);
	str[0] = '0';
	ch = n;
	while (ch > 0)
	{
		str[--cnt] = (ch % base) < 10 ?
	('0' + (ch % base)) : (pr_par->hex_sym + (ch % base - 10));
		ch /= base;
	}
	if (pr_par->type != 'f')
		return (ft_itoa_option(str, pr_par, 1, (n == 0) ? 1 : 0));
	else
		return (str);
}
