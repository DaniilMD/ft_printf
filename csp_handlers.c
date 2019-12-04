

#include "ft_printf.h"

void	c_handler(t_print_params *pr_par, va_list args)
{
	int	i;

	i = 0;
	while (i < pr_par->padding_size)
	{
		if ((pr_par->align_to_left == 1 && i == 0) || 
(i == pr_par->padding_size - 1 && pr_par->align_to_left == 0))
			buff_filler(pr_par, va_arg(args, int));
		else
		{
			if (pr_par->use_zeros == 1)
				buff_filler(pr_par, '0');
			else
				buff_filler(pr_par, ' ');
		}
		i++;
	}
}

void	s_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;
	char	*old;

	i = 0;
	str = va_arg(args, char *);
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
		{
			if (i < pr_par->precision)
				buff_filler(pr_par, *str++);
			else
			//{
				//if (pr_par->use_zeros == 1)
				//	buff_filler(pr_par, '0');
				//else
					buff_filler(pr_par, ' ');
			//}
		}
		else
		{
			if (i < pr_par->padding_size - pr_par->precision)
			//{
				//if (pr_par->use_zeros == 1)
				//	buff_filler(pr_par, '0');
				//else
					buff_filler(pr_par, ' ');
			//}
			else
				buff_filler(pr_par, *str++);
		}
		i++;
	}
	ft_strdel(&old);
}

void	p_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;
	char	*str1;
	char	*str3;

	i = 0;
	str = "0x10";
	str3 = ft_itoa_base(va_arg(args, int), 16, '0', 'a');
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
	ft_strdel(&str);
}

