

#include "ft_printf.h"

void	c_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	c;

	i = 0;
	c = va_arg(args, int);
	if (pr_par->padding_size == 0)
		pr_par->padding_size = 1;
	if (pr_par->precision == 0)
		pr_par->precision = 1;
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
		{
			if (i == 0)
				buff_filler(pr_par, c);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
		}
		else
		{
			if (i == pr_par->padding_size - 1)
				buff_filler(pr_par, c);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
		}
		i++;
	}
}

void	s_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;

	i = 0;
	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";
	if (pr_par->precision == 0)
		pr_par->precision = ft_strlen(str);
	if ((int)ft_strlen(str) < pr_par->precision)
		pr_par->precision = ft_strlen(str);
	if (pr_par->padding_size == 0)
		pr_par->padding_size = pr_par->precision;//ft_strlen(str);
	//printf("\nstr: %s, padding: %d, precision: %d\n",
	//str, pr_par->padding_size, pr_par->precision);
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
		{
			if (i < pr_par->precision)
				buff_filler(pr_par, *str++);
			else
				buff_filler(pr_par, ' ');
		}
		else
		{
			if (i < pr_par->padding_size - pr_par->precision)
				buff_filler(pr_par, ' ');
			else
				buff_filler(pr_par, *str++);
		}
		i++;
	}
}

void	p_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;
	char	*str1;
	char	*str3;

	i = 0;
	str = "0x10";
	str3 = ft_itoa_base(va_arg(args, int), 16, pr_par);
	str1 = ft_strjoin(str, str3);
	str = str1;
	ft_strdel(&str3);
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
		{
			if (i < 11)
				buff_filler(pr_par, *str1++);
			else
				buff_filler(pr_par, ' ');
		}
		else
		{
			if (i < pr_par->padding_size - 11)
				buff_filler(pr_par, ' ');
			else
				buff_filler(pr_par, *str1++);
		}
		i++;
	}
}

