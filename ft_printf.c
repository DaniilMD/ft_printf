
#include "ft_printf.h"

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

}

void	percent_handler(t_print_params *pr_par)
{
	int		i;
	char	c;

	i = 0;
	c = '%';
	if (pr_par->padding_size == 0)
		pr_par->padding_size = 1;
	if (pr_par->precision == 0)
		pr_par->precision = 1;
	while (i < pr_par->padding_size)
	{
		//if ((pr_par->align_to_left == 1 && i == 0) || 
//(i == pr_par->padding_size - 1 && pr_par->align_to_left == 0))
		//	buff_filler(pr_par, va_arg(args, int));
		//else
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

void	options_handler(t_print_params *pr_par, va_list args)
{
	param_zeroer(pr_par);
	flags_handler(pr_par);
	width_handler(pr_par, args);
	precision_handler(pr_par, args);
	length_handler(pr_par);
	type_handler(pr_par);
	/*printf("\n|||||||||||||||||||||||||\n\ncurr_i: %d\nprint_sign: %d\nuse_zeros: %d\nalign_to_left: %d\nspace_option: %d\n\
alt_format: %d\npadding_size: %d\nprecision: %d\nlength: %c\ntype: %c\n", pr_par->curr_i, pr_par->print_sign, pr_par->use_zeros, pr_par->align_to_left, pr_par->space_option, pr_par->alt_format, pr_par->padding_size, pr_par->precision, pr_par->length, pr_par->type);
*/

	if (pr_par->type == '%')
		percent_handler(pr_par);
		//buff_filler(pr_par, '%');
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
		ouxX_handler(pr_par, args);
	//else
	//	f_handler(pr_par, args);
}

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
	//pr_par->str = NULL;
	//pr_par->buff_cntr = 0;
	//pr_par->printf_buf = ft_strnew(1024);
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
		}	
	}
	return (pr_par.buff_cntr);//ft_strlen(printf_buf));
}

int		ft_printf(const char *format, ...)
{
	char	*printf_buf;
	va_list	args;
	int		printed;
	int		i;
	
	printf_buf = ft_strnew(1024);//(char*)malloc(sizeof(char) * 1024);
	//printf_buf = NULL;
	//printf("\n\nstart: %s\n\n", printf_buf);
	va_start(args, format);
	printed = just_printer(printf_buf, format, args);
	va_end(args);

	//printf("\nfinish: %s", printf_buf);
	//ft_putstr(printf_buf);
	i = 0;
	while (i < printed)
	{
		ft_putchar(printf_buf[i]);
		i++;
	}
	return (printed);
}
