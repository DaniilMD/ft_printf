#include "ft_printf.h"

void	init_pr_par(t_print_params *pr_par)
{
	int i;

	i = 0;
	while (i < 1024)
	{
		pr_par->printf_buf[i] = '\0';
		i++;
	}
	pr_par->align_to_left = 0;
	pr_par->alt_format = 0;
	pr_par->buff_cntr = 0;
	pr_par->curr_i = 0;
	pr_par->length = 0;
	pr_par->padding_size = 0;
	pr_par->precision = -1;
	pr_par->print_sign = 0;
	pr_par->space_option = 0;
	pr_par->type = 0;
	pr_par->use_zeros = 0;
	pr_par->hex_sym = 'a';
	pr_par->prec_indic = 0;
	pr_par->str_start = NULL;
}

void	param_zeroer(t_print_params *pr_par)
{
	pr_par->align_to_left = 0;
	pr_par->alt_format = 0;
	pr_par->length = 0;
	pr_par->padding_size = 0;
	pr_par->precision = 0;
	pr_par->print_sign = 0;
	pr_par->space_option = 0;
	pr_par->type = 0;
	pr_par->use_zeros = 0;
	pr_par->hex_sym = 'a';
	pr_par->prec_indic = 0;
	pr_par->str_start = NULL;
}

void	options_handler(t_print_params *pr_par, va_list args)
{
	param_zeroer(pr_par);
	flags_handler(pr_par);
	width_handler(pr_par, args);
	precision_handler(pr_par, args);
	length_handler(pr_par);
	type_handler(pr_par);
	if (pr_par->str[pr_par->curr_i + 1] == '%' && pr_par->type == 0)
		pr_par->type = '%';
	if (pr_par->type == '%')
		percent_handler(pr_par);
	else if (pr_par->type == 'c')
		c_handler(pr_par, args);
	else if (pr_par->type == 's')
		s_handler(pr_par, args);
	else if (pr_par->type == 'p')
		p_handler(pr_par, args);
	else if (pr_par->type == 'd' || pr_par->type == 'i')
		di_handler(pr_par, args);
	else if (pr_par->type == 'o' || pr_par->type == 'u'
	|| pr_par->type == 'x' || pr_par->type == 'X')
		oux_xx_handler(pr_par, args);
	else if (pr_par->type == 'f')
		f_handler(pr_par, args);
}

int		just_printer(char *printf_buf, const char *str, va_list args)
{
	t_print_params	pr_par;

	pr_par.printf_buf = printf_buf;
	init_pr_par(&pr_par);
	pr_par.str = str;
	while (str[pr_par.curr_i] != '\0')
	{
		if (str[pr_par.curr_i] != '%')
		{
			printf_buf[pr_par.buff_cntr] = str[pr_par.curr_i];
			pr_par.buff_cntr++;
			pr_par.curr_i++;
		}
		else
		{
			pr_par.curr_i++;
			options_handler(&pr_par, args);
			if (pr_par.str_start != NULL)
				free(pr_par.str_start);
		}
	}
	return (pr_par.buff_cntr);
}

int		ft_printf(const char *format, ...)
{
	char	*printf_buf;
	va_list	args;
	int		printed;

	printf_buf = ft_strnew(1024);
	va_start(args, format);
	printed = just_printer(printf_buf, format, args);
	va_end(args);
	write(1, printf_buf, printed);
	ft_strdel(&printf_buf);
	return (printed);
}
