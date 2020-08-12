#include "ft_printf.h"

int		f_pow(int num, int grade)
{
	int i;
	int res;

	i = 0;
	res = 1;
	while (i < grade)
	{
		res *= num;
		i++;
	}
	return (res);
}

void	f_printer(t_print_params *pr_par, char *str)
{
	int i;
	int len;

	i = 0;
	str = extra_work(pr_par, str);
	len = ft_strlen(str);
	pr_par->str_start = str;
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
			if (i < len)
				buff_filler(pr_par, *str++);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
		else
		{
			if (i < pr_par->padding_size - len)
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
			else
				buff_filler(pr_par, *str++);
		}
		i++;
	}
}

char	*f_str_filler(t_print_params *pr_par, long double f_part, char *str)
{
	int i;

	i = 1;
	if (str != NULL)
	{
		f_part = f_part * f_pow(10, pr_par->precision);
		if ((long long)(f_part * 10) % 10 > 5)
			f_part++;
		str = ft_strjoin_free(str, ".", 1);
		str = ft_strjoin_free(str,
		ft_itoa_base_uns((long long)f_part, 10, pr_par), 3);
		if (f_part == 0)
		{
			while (i < pr_par->precision)
			{
				str = ft_strjoin_free(str, "0", 1);
				i++;
			}
		}
	}
	return (str);
}

void	f_handler(t_print_params *pr_par, va_list args)
{
	long long	i_part;
	long double	f_part;
	char		*str;

	if (pr_par->length == 'l')
		f_part = va_arg(args, double);
	else if (pr_par->length == 'D')
		f_part = va_arg(args, long double);
	else
		f_part = va_arg(args, double);
	if (pr_par->prec_indic == 0)
		pr_par->precision = 6;
	i_part = (long long)f_part;
	str = ft_itoa_base((long long)i_part, 10, pr_par);
	if (i_part < 0)
	{
		i_part *= -1;
		f_part *= -1;
	}
	f_part = f_part - (double)i_part;
	str = f_str_filler(pr_par, f_part, str);
	f_printer(pr_par, str);
}
