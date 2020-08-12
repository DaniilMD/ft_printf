#include "ft_printf.h"

void	csp_params_changer(t_print_params *pr_par, char *str)
{
	if (pr_par->type == 'c')
	{
		if (pr_par->padding_size == 0)
			pr_par->padding_size = 1;
		if (pr_par->precision == 0)
			pr_par->precision = 1;
		return ;
	}
	if ((int)ft_strlen(str) < pr_par->precision)
		pr_par->precision = ft_strlen(str);
	if (pr_par->padding_size == 0)
		pr_par->padding_size = pr_par->precision;
	if (pr_par->type == 's')
	{
		if (pr_par->precision == 0 && pr_par->prec_indic == 0)
			pr_par->precision = ft_strlen(str);
		if (pr_par->padding_size < pr_par->precision)
			pr_par->padding_size = pr_par->precision;
		pr_par->str_start = str;
		return ;
	}
	if (pr_par->precision == 0)
		pr_par->precision = ft_strlen(str);
	if (pr_par->padding_size < (int)ft_strlen(str))
		pr_par->padding_size = ft_strlen(str);
}

void	c_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	c;

	i = 0;
	c = va_arg(args, int);
	csp_params_changer(pr_par, NULL);
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
			if (i == 0)
				buff_filler(pr_par, c);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
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

	i = -1;
	str = ft_strjoin_free(va_arg(args, char *), "", 0);
	if (str == NULL)
		str = ft_strjoin_free("(null)", "", 0);
	csp_params_changer(pr_par, str);
	while (++i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
			if (i < pr_par->precision)
				buff_filler(pr_par, *str++);
			else
				buff_filler(pr_par, ' ');
		else
		{
			if (i < pr_par->padding_size - pr_par->precision)
				buff_filler(pr_par, ' ');
			else
				buff_filler(pr_par, *str++);
		}
	}
}

void	p_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;
	int		len;

	i = -1;
	str = ft_itoa_base((long long)va_arg(args, void*), 16, pr_par);
	str = ft_strjoin_free("0x", str, 2);
	csp_params_changer(pr_par, str);
	len = (int)ft_strlen(str);
	pr_par->str_start = str;
	while (++i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
			if (i < len)
				buff_filler(pr_par, *str++);
			else
				buff_filler(pr_par, ' ');
		else
		{
			if (i < pr_par->padding_size - len)
				buff_filler(pr_par, ' ');
			else
				buff_filler(pr_par, *str++);
		}
	}
}

void	percent_handler(t_print_params *pr_par)
{
	int		i;
	char	c;

	i = -1;
	c = '%';
	if (pr_par->padding_size == 0)
		pr_par->padding_size = 1;
	if (pr_par->precision == 0)
		pr_par->precision = 1;
	while (++i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
			if (i == 0)
				buff_filler(pr_par, c);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
		else
		{
			if (i == pr_par->padding_size - 1)
				buff_filler(pr_par, c);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
		}
	}
	pr_par->curr_i++;
}
