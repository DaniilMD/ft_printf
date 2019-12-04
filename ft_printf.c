
#include "ft_printf.h"

void	buff_filler(t_print_params *pr_par, int sym)
{
	pr_par->printf_buf[pr_par->buff_cntr] = sym;
	pr_par->buff_cntr++;
}


char	*ft_itoa_base(int n, int base)
{
	long long	ch;
	char		*str;
	int			cnt;
	int			sign;

	sign = (n < 0) ? -1 : 1;
	cnt = (n < 0) ? 2 : 1;
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
	('0' + (ch % base)) : ('a' + (ch % base - 10));
		ch /= base;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}


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
	str3 = ft_itoa_base(va_arg(args, int), 16);
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


void	options_handler(t_print_params *pr_par, va_list args)
{
	flags_handler(pr_par, args);
	width_handler(pr_par, args);
	precision_handler(pr_par, args);
	length_handler(pr_par, args);
	type_handler(pr_par, args);
	printf("curr_i: %d\nprint_sign: %d\nuse_zeros: %d\nalign_to_left: %d\nspace_option: %d\n\
alt_format: %d\npadding_size: %d\nprecision: %d\nlength: %d\ntype: %c\n", pr_par->curr_i, pr_par->print_sign, pr_par->use_zeros, pr_par->align_to_left, pr_par->space_option, pr_par->alt_format, pr_par->padding_size, pr_par->precision, pr_par->length, pr_par->type);
	if (pr_par->type == '%')
		buff_filler(pr_par, '%');
	else if (pr_par->type == 'c')
		c_handler(pr_par, args);
	else if (pr_par->type == 's')
		s_handler(pr_par, args);
	else if (pr_par->type == 'p')
		p_handler(pr_par, args);
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
	return (111111111);
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
	ft_printf("aa%%aaa123%-20p111111abc123", str);
	printf("\naa%%aaa123%-20p111111abc123\n\n", str);
	//ft_printf("aa%%aaa123%0-20.3s111111abc123", str);
	//printf("\naa%%aaa123%0-20.3s111111abc123\n\n", str);
	
	//printf("\n%s\n%d", ft_itoa_base(str, 16), str);
	return (0);
}

