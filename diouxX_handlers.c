#include "ft_printf.h"

long long		length_changer(t_print_params *pr_par, va_list args)
{
	long long	num;

	if (pr_par->type == 'd' || pr_par->type == 'i')
	{
		if (pr_par->length == 'H')
			num = (char)va_arg(args, int);
		else if (pr_par->length == 'h')
			num = (short)va_arg(args, int);
		else if (pr_par->length == 'l')
			num = va_arg(args, long);
		else if (pr_par->length == 'L')
			num = (long long)va_arg(args, long long int);
		else
			num = (long long)va_arg(args, int);
		//if (num == -9223372036854775808)
		//	printf("wegergrh");
	}
	else
	{
		if (pr_par->length == 'H')
			num = (unsigned char)va_arg(args, int);
		else if (pr_par->length == 'h')
			num = (unsigned short)va_arg(args, int);
		else if (pr_par->length == 'l')
			num = (long long)va_arg(args, unsigned long);
		else if (pr_par->length == 'L')
			num = (long long)va_arg(args, unsigned long long);
		else
		{
			if (pr_par->type == 'u')
				num = (long long)va_arg(args, unsigned int);
			else
				num = (long long)va_arg(args, int);//long long);
		}
	}
	printf("\nnum_getter1111: %lld", (long long)0);
	return (num);
}

char	*num_getter(t_print_params *pr_par, va_list args)
{
	char		*str;
	long long	num;

	num = length_changer(pr_par, args);

	//if (num == -9223372036854775808)
	//	return ("-9223372036854775808");

	//printf("\nnum_getter: %lld", num);
	if (pr_par->type == 'd' || pr_par->type == 'i' || pr_par->type == 'u') 
		str = ft_itoa_base(num, 10, pr_par);
	else if (pr_par->type == 'o')
		str = ft_itoa_base(num, 8, pr_par);
	else if (pr_par->type == 'x')
		str = ft_itoa_base(num, 16, pr_par);
	else if (pr_par->type == 'X')
	{
		pr_par->hex_sym = 'A';
		str = ft_itoa_base(num, 16, pr_par);
	}
	else
		str = NULL;
	//printf("\n\nNum getter: %s\n\n", str);
	return (str);
}

char	*extra_work(t_print_params *pr_par, char *str)
{
	
	/*if (pr_par->prec_indic == 1 && pr_par->precision == 0)
	{
		str = ft_strnew(0);
		return (str);
	}*/
	if (pr_par->precision > 0 || pr_par->align_to_left == 1)// || pr_par->padding_size != 0)
		pr_par->use_zeros = 0;
	if (pr_par->padding_size == 0 || pr_par->padding_size < (int)ft_strlen(str))
		pr_par->padding_size = ft_strlen(str);
	
	return (str);
}

void	di_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;
	int		len;

	
	str = num_getter(pr_par, args);
	str = extra_work(pr_par, str);
	len = ft_strlen(str);
	//printf("\n\ndi: %s\n\n", str);
	/*printf("\ncurr_i: %d\nprint_sign: %d\nuse_zeros: %d\nalign_to_left: %d\nspace_option: %d\n\
alt_format: %d\npadding_size: %d\nprecision: %d\nlength: %c\ntype: %c\n", pr_par->curr_i, pr_par->print_sign, pr_par->use_zeros, pr_par->align_to_left, pr_par->space_option, pr_par->alt_format, pr_par->padding_size, pr_par->precision, pr_par->length, pr_par->type);
	printf("\n\nlen: %d\n\n", len);


	printf("\n???????");
	printf("\nbuf0: %s", pr_par->printf_buf);
	printf("\n???????\n");*/
	i = 0;
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
		{
			if (i < len)//pr_par->precision)
				buff_filler(pr_par, *str++);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
		}
		else
		{
			if (i < pr_par->padding_size - len)//pr_par->precision)
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
			else
				buff_filler(pr_par, *str++);
		}
		i++;
		//printf("%d", i);
	}
	//printf("???????");
//	printf("buf: %s", pr_par->printf_buf);
	//printf("???????");
}

void	ouxX_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	str = num_getter(pr_par, args);
	str = extra_work(pr_par, str);
	len = ft_strlen(str);
	//printf("\n\nlen: %d, padding: %d\nouxX: %s\n\n", len, pr_par->padding_size, str);
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
		{
			if (i < len)//pr_par->precision)
				buff_filler(pr_par, *str++);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
		}
		else
		{
			if (i < pr_par->padding_size - len)//pr_par->precision)
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
			else
				buff_filler(pr_par, *str++);
		}
		i++;
	}
//	printf("\n???????");
//	printf("\nbuf: %s\nbuff_cntr: %d", pr_par->printf_buf, pr_par->buff_cntr);
//	printf("\n???????");
}