
#include "ft_printf.h"

long long		length_changer(t_print_params *pr_par, va_list args)
{
	long long num;
	if (pr_par->type == 'd' || pr_par->type == 'i')
	{
		if (pr_par->length == 'H')
			num = (char)va_arg(args, int);
		else if (pr_par->length == 'h')
			num = (short)va_arg(args, int);
		else if (pr_par->length == 'l')
			num = va_arg(args, long);
		else if (pr_par->length == 'L')
			num = (long long)va_arg(args, long long);
		else
			num = va_arg(args, long long);
	}
	else
	{
		if (pr_par->length == 'H')
			num = (unsigned char)va_arg(args, int);
		else if (pr_par->length == 'h')
			num = (unsigned short)va_arg(args, int);
		else if (pr_par->length == 'l')
			num = va_arg(args, unsigned long);
		else if (pr_par->length == 'L')
			num = va_arg(args, unsigned long long);
		else
			num = va_arg(args, long long);
	}
	printf("\n\nnum :%lld\n\n", num);
	return (num);
}

char	*num_getter(t_print_params *pr_par, va_list args)
{
	char	*str;
	long long		num;

	num = length_changer(pr_par, args);//va_arg(args, int);
	//printf("\n\nnum :%lld\n\n", num);
	if ((pr_par->space_option == 1 || pr_par->print_sign == 1)
	&& (pr_par->type == 'd' || pr_par->type == 'i')) 
	{
		if (pr_par->print_sign == 1)
			str = ft_itoa_base(num, 10, '+', 'a');
		else
			str = ft_itoa_base(num, 10, ' ', 'a');
	}
	else
	{
		if (pr_par->type == 'd' || pr_par->type == 'i') 
			str = ft_itoa_base(num, 10, '0', 'a');
		else if (pr_par->type == 'o')
			str = ft_itoa_base(num, 8, '0', 'a');
		else if (pr_par->type == 'u')
			str = ft_itoa_base(num, 10, '0', 'a');
		else if (pr_par->type == 'x')
			str = ft_itoa_base(num, 16, '0', 'a');
		else if (pr_par->type == 'X')
			str = ft_itoa_base(num, 16, '0', 'A');
	}
	return (str);
}

char	*extra_work(t_print_params *pr_par, va_list args, char *str)
{
	char *tmp;
	char *tmp2;

	if (pr_par->precision == 0)
		pr_par->precision = ft_strlen(str);
	if (pr_par->padding_size == 0)
		pr_par->padding_size = ft_strlen(str);
	if (pr_par->alt_format == 1)
	{
		if (pr_par->type == 'x')
		{
			tmp = "0x";
			str = ft_strjoin(tmp, str);
			//buff_filler(pr_par, '0');
			//buff_filler(pr_par, 'x');
		}
		else if (pr_par->type == 'X')
		{
			//tmp = ft_strjoin("0X", str);
			//return (tmp);
			//str = tmp;
			//free(str);
			//str = tmp;
			//str = ft_strjoin("0X", str);
			//buff_filler(pr_par, '0');
			//buff_filler(pr_par, 'X');
		}
		else if (pr_par->type == 'o')
		{
			//buff_filler(pr_par, '0');
		}
		else
			tmp = str;
	}
	else
		tmp = str;
	//free(str);
	//str = tmp;
	return (tmp);
}

void	di_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;

	i = 0;
	str = num_getter(pr_par, args);
	//printf("\n\nstr %s||||\n\n", str);
	extra_work(pr_par, args, str);
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

void	ouxX_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;
	//char	*str0;

	i = 0;
	str = num_getter(pr_par, args);
	printf("\n\nstr %s||||\n\n", str);
	extra_work(pr_par, args, str);
	printf("\n\nstr 2.0 %s||||\n\n", str);
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

void	options_handler(t_print_params *pr_par, va_list args)
{
	flags_handler(pr_par, args);
	width_handler(pr_par, args);
	precision_handler(pr_par, args);
	length_handler(pr_par, args);
	type_handler(pr_par, args);
	printf("\ncurr_i: %d\nprint_sign: %d\nuse_zeros: %d\nalign_to_left: %d\nspace_option: %d\n\
alt_format: %d\npadding_size: %d\nprecision: %d\nlength: %c\ntype: %c\n", pr_par->curr_i, pr_par->print_sign, pr_par->use_zeros, pr_par->align_to_left, pr_par->space_option, pr_par->alt_format, pr_par->padding_size, pr_par->precision, pr_par->length, pr_par->type);

/*
	int			curr_i;
	int			print_sign;
	int			use_zeros;
	int			align_to_left;
	int			space_option;
	int			alt_format;
	int			padding_size;
	int			precision;
	int			length;
	char		type;
*/

	if (pr_par->type == '%')
		buff_filler(pr_par, '%');
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
	//csp
	//diouxX with hh l h ll
	//f with 1 L
	//%%
	//#0-+ and space
}

int		just_printer(char *printf_buf, const char *str, va_list args)
{
	t_print_params	pr_par;

	pr_par.curr_i = 0;
	pr_par.buff_cntr = 0;
	pr_par.printf_buf = printf_buf;
	pr_par.str = str;
	//pr_par.args = args;
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
	



	return (9999999);
}

int		ft_printf(const char *format, ...)
{
	char	printf_buf[1024];
	va_list	args;
	int		printed;

	va_start(args, format);
	printed = just_printer(printf_buf, format, args);
	va_end(args);

	ft_putstr(printf_buf);
	

	return (printed);
}

int		main(int argc, char **argv)
{
	//printf("",);
	char *str = "abcd";
   ft_printf("aa%%aaa123||||||||||||||%#20llX||||||111111abc123", (long long)123456789);
	printf("\naa%%aaa123||||||||||||||%#20llX||||||111111abc123\n\n", (long long)123456789);
	//ft_printf("aa%%aaa123%0-20.3s111111abc123", str);
	//printf("\naa%%aaa123%0-20.3s111111abc123\n\n", str);
	
	//printf("\n%s\n%d", ft_itoa_base(str, 16), st, 'a'r);
	return (0);
}

