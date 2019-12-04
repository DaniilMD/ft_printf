#include "ft_printf.h"

void	flags_handler(t_print_params *pr_par, va_list args)
{
	while ((pr_par->str[pr_par->curr_i] == '#' || pr_par->str[pr_par->curr_i] == '0'
	|| pr_par->str[pr_par->curr_i] == '-' || pr_par->str[pr_par->curr_i] == '+'
	|| pr_par->str[pr_par->curr_i] == ' ') && pr_par->str[pr_par->curr_i] != '\0')
	{
		if (pr_par->str[pr_par->curr_i] == '#')
			pr_par->alt_format = 1;
		if (pr_par->str[pr_par->curr_i] == '0')
			pr_par->use_zeros = 1;
		if (pr_par->str[pr_par->curr_i] == '-')
			pr_par->align_to_left = 1;
		if (pr_par->str[pr_par->curr_i] == '+')
			pr_par->print_sign = 1;
		if (pr_par->str[pr_par->curr_i] == ' ')
			pr_par->space_option = 1;
		pr_par->curr_i++;

		printf("%c ", pr_par->str[pr_par->curr_i - 1]);
	} 
}

void	width_handler(t_print_params *pr_par, va_list args)
{
	while (((pr_par->str[pr_par->curr_i]  >= '0' && pr_par->str[pr_par->curr_i] <= '9')
	|| pr_par->str[pr_par->curr_i] == '*') && pr_par->str[pr_par->curr_i] != '\0')
	{
		if (pr_par->str[pr_par->curr_i] == '*')
			pr_par->padding_size = va_arg(args, int);
		if ((pr_par->str[pr_par->curr_i]  >= '0' && pr_par->str[pr_par->curr_i] <= '9') &&
		(pr_par->str[pr_par->curr_i - 1] < '0' || pr_par->str[pr_par->curr_i - 1] > '9'))
			pr_par->padding_size = ft_atoi(&pr_par->str[pr_par->curr_i]);
		pr_par->curr_i++;

		printf("%c ", pr_par->str[pr_par->curr_i - 1]);
	} 
}

void	precision_handler(t_print_params *pr_par, va_list args)
{
	while (((pr_par->str[pr_par->curr_i]  >= '0' && pr_par->str[pr_par->curr_i] <= '9')
	|| pr_par->str[pr_par->curr_i] == '*' || pr_par->str[pr_par->curr_i] == '.') && pr_par->str[pr_par->curr_i] != '\0')
	{
		if (pr_par->str[pr_par->curr_i] == '*')
			pr_par->precision = va_arg(args, int);
		if ((pr_par->str[pr_par->curr_i]  >= '0' && pr_par->str[pr_par->curr_i] <= '9') &&
		(pr_par->str[pr_par->curr_i - 1]  < '0' || pr_par->str[pr_par->curr_i - 1] > '9'))
			pr_par->precision = ft_atoi(&pr_par->str[pr_par->curr_i]);
		pr_par->curr_i++;

		printf("%c ", pr_par->str[pr_par->curr_i - 1]);
	} 
}

void	length_handler(t_print_params *pr_par, va_list args)
{
	while ((pr_par->str[pr_par->curr_i]  == 'h' || pr_par->str[pr_par->curr_i]  == 'l') && pr_par->str[pr_par->curr_i] != '\0')
	{
		if (pr_par->str[pr_par->curr_i] == 'l' && pr_par->str[pr_par->curr_i + 1] != 'l' && pr_par->str[pr_par->curr_i - 1] != 'l')
			pr_par->length = 'l';
			//		l
			//make long
		if (pr_par->str[pr_par->curr_i] == 'h' && pr_par->str[pr_par->curr_i + 1] != 'h' && pr_par->str[pr_par->curr_i - 1] != 'h')
			pr_par->length = 'h';
			//make short
			//		h
		if (pr_par->str[pr_par->curr_i] == 'l' && pr_par->str[pr_par->curr_i + 1] == 'l')
			pr_par->length = 'L';
			//make long long
			//		ll
		if (pr_par->str[pr_par->curr_i] == 'h' && pr_par->str[pr_par->curr_i + 1] == 'h')
			pr_par->length = 'H';
			//make char
			//		hh
		pr_par->curr_i++;

		printf("%c ", pr_par->str[pr_par->curr_i - 1]);
	} 
}

void	type_handler(t_print_params *pr_par, va_list args)
{
	while ((pr_par->str[pr_par->curr_i] == 'c' || pr_par->str[pr_par->curr_i] == 's' || pr_par->str[pr_par->curr_i] == 'p'
	|| pr_par->str[pr_par->curr_i] == 'd' || pr_par->str[pr_par->curr_i] == 'i' || pr_par->str[pr_par->curr_i] == 'o'
	|| pr_par->str[pr_par->curr_i] == 'u' || pr_par->str[pr_par->curr_i] == 'x' || pr_par->str[pr_par->curr_i] == 'X'
	|| pr_par->str[pr_par->curr_i] == 'f' || pr_par->str[pr_par->curr_i] == '%') && pr_par->str[pr_par->curr_i] != '\0')
	{
		pr_par->type = pr_par->str[pr_par->curr_i];
		pr_par->curr_i++;

		printf("%c ", pr_par->str[pr_par->curr_i - 1]);
	} 
}

