
#include "ft_printf.h"

void	flags_handler(char *printf_buf, const char *str, va_list args, t_print_params *pr_par)
{
	while ((str[pr_par->curr_i] == '#' || str[pr_par->curr_i] == '0'
	|| str[pr_par->curr_i] == '-' || str[pr_par->curr_i] == '+'
	|| str[pr_par->curr_i] == ' ') && str[pr_par->curr_i] != '\0')
	{
		if (str[pr_par->curr_i] == '#')
			pr_par->alt_format = 1;
		if (str[pr_par->curr_i] == '0')
			pr_par->use_zeros = 1;
		if (str[pr_par->curr_i] == '-')
			pr_par->align_to_left = 1;
		if (str[pr_par->curr_i] == '+')
			pr_par->print_sign = 1;
		if (str[pr_par->curr_i] == ' ')
			pr_par->space_option = 1;
		pr_par->curr_i++;

		printf("%c ", str[pr_par->curr_i - 1]);
	} 
}

void	width_handler(char *printf_buf, const char *str, va_list args, t_print_params *pr_par)
{
	while (((str[pr_par->curr_i]  >= '0' && str[pr_par->curr_i] <= '9')
	|| str[pr_par->curr_i] == '*') && str[pr_par->curr_i] != '\0')
	{
		if (str[pr_par->curr_i] == '*')
			pr_par->padding_size = va_arg(args, int);
		if ((str[pr_par->curr_i]  >= '0' && str[pr_par->curr_i] <= '9') &&
		(str[pr_par->curr_i - 1]  < '0' || str[pr_par->curr_i - 1] > '9'))
			pr_par->padding_size = ft_atoi(&str[pr_par->curr_i]);
		pr_par->curr_i++;

		printf("%c ", str[pr_par->curr_i - 1]);
	} 
}

void	precision_handler(char *printf_buf, const char *str, va_list args, t_print_params *pr_par)
{
	while (((str[pr_par->curr_i]  >= '0' && str[pr_par->curr_i] <= '9')
	|| str[pr_par->curr_i] == '*' || str[pr_par->curr_i] == '.') && str[pr_par->curr_i] != '\0')
	{
		if (str[pr_par->curr_i] == '*')
			pr_par->precision = va_arg(args, int);
		if ((str[pr_par->curr_i]  >= '0' && str[pr_par->curr_i] <= '9') &&
		(str[pr_par->curr_i - 1]  < '0' || str[pr_par->curr_i - 1] > '9'))
			pr_par->precision = ft_atoi(&str[pr_par->curr_i]);
		pr_par->curr_i++;

		printf("%c ", str[pr_par->curr_i - 1]);
	} 
}

void	length_handler(char *printf_buf, const char *str, va_list args, t_print_params *pr_par)
{
	while ((str[pr_par->curr_i]  == 'h' || str[pr_par->curr_i]  == 'l') && str[pr_par->curr_i] != '\0')
	{
		if (str[pr_par->curr_i] == 'l' && str[pr_par->curr_i + 1] != 'l' && str[pr_par->curr_i - 1] != 'l')
			pr_par->length = 1;
			//		l
			//make long
		if (str[pr_par->curr_i] == 'h' && str[pr_par->curr_i + 1] != 'h' && str[pr_par->curr_i - 1] != 'h')
			pr_par->length = 2;
			//make short
			//		h
		if (str[pr_par->curr_i] == 'l' && str[pr_par->curr_i + 1] == 'l')
			pr_par->length = 3;
			//make long long
			//		ll
		if (str[pr_par->curr_i] == 'h' && str[pr_par->curr_i + 1] == 'h')
			pr_par->length = 4;
			//make char
			//		hh
		pr_par->curr_i++;

		printf("%c ", str[pr_par->curr_i - 1]);
	} 
}

void	type_handler(char *printf_buf, const char *str, va_list args, t_print_params *pr_par)
{
	while ((str[pr_par->curr_i] == 'c' || str[pr_par->curr_i] == 's' || str[pr_par->curr_i] == 'p'
	|| str[pr_par->curr_i] == 'd' || str[pr_par->curr_i] == 'i' || str[pr_par->curr_i] == 'o'
	|| str[pr_par->curr_i] == 'u' || str[pr_par->curr_i] == 'x' || str[pr_par->curr_i] == 'X'
	|| str[pr_par->curr_i] == 'f' || str[pr_par->curr_i] == '%') && str[pr_par->curr_i] != '\0')
	{
		pr_par->type = str[pr_par->curr_i];
		pr_par->curr_i++;

		printf("%c ", str[pr_par->curr_i - 1]);
	} 
}



void	options_handler(char *printf_buf, const char *str, va_list args, t_print_params *pr_par)
{
	flags_handler(printf_buf, str, args, pr_par);
	width_handler(printf_buf, str, args, pr_par);
	precision_handler(printf_buf, str, args, pr_par);
	length_handler(printf_buf, str, args, pr_par);
	type_handler(printf_buf, str, args, pr_par);
	if (pr_par->type == '%')
	{
		printf_buf[]
	}

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
			options_handler(printf_buf, str, args, &pr_par);
		}	
	}
	printf("curr_i: %d\nprint_sign: %d\nuse_zeros: %d\nalign_to_left: %d\nspace_option: %d\n\
alt_format: %d\npadding_size: %d\nprecision: %d\nlength: %d\ntype: %c\n", pr_par.curr_i, pr_par.print_sign, pr_par.use_zeros, pr_par.align_to_left, pr_par.space_option, pr_par.alt_format, pr_par.padding_size, pr_par.precision, pr_par.length, pr_par.type);


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
	ft_printf("aaaaa000000000%#0*.7hhXabc123", 3, 20);
	return (0);
}
