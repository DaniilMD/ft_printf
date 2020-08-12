#include "ft_printf.h"

void	length_changer_di(t_print_params *pr_par, va_list args)
{
	long long			num;

	if (pr_par->length == 'H')
		num = (char)va_arg(args, int);
	else if (pr_par->length == 'h')
		num = (short)va_arg(args, int);
	else if (pr_par->length == 'l')
		num = va_arg(args, long);
	else if (pr_par->length == 'L')
		num = (long long)va_arg(args, long long);
	else
		num = (long long)va_arg(args, int);
	pr_par->num = num;
}

void	length_changer_u(t_print_params *pr_par, va_list args)
{
	unsigned long long	extra_num;

	if (pr_par->type == 'u')
	{
		if (pr_par->length == 'H')
			extra_num = (unsigned char)va_arg(args, int);
		else if (pr_par->length == 'h')
			extra_num = (unsigned short)va_arg(args, int);
		else if (pr_par->length == 'l')
			extra_num = (unsigned long long)va_arg(args, unsigned long);
		else if (pr_par->length == 'L')
			extra_num = (unsigned long long)va_arg(args, unsigned long long);
		else
			extra_num = (unsigned long long)va_arg(args, unsigned int);
		pr_par->num_u = extra_num;
	}
}

void	length_changer_ox_xx(t_print_params *pr_par, va_list args)
{
	long long			num;

	if (pr_par->length == 'H')
		num = (unsigned char)va_arg(args, int);
	else if (pr_par->length == 'h')
		num = (unsigned short)va_arg(args, int);
	else if (pr_par->length == 'l')
		num = (long long)va_arg(args, unsigned long);
	else if (pr_par->length == 'L')
		num = (long long)va_arg(args, unsigned long long);
	else
		num = (long long)va_arg(args, int);
	pr_par->num = num;
}

char	*exceptions(t_print_params *pr_par)
{
	if (pr_par->num - 1 == 9223372036854775807)
		return (ft_strjoin_free("-9223372036854775808", "", 0));
	if (pr_par->num == (long long)ULONG_MAX && pr_par->type == 'o'
	&& pr_par->length == 'l')
		return (ft_strjoin_free("1777777777777777777777", "", 0));
	if (pr_par->num == (long long)ULONG_MAX && pr_par->type == 'x'
	&& pr_par->length == 'l')
		return (ft_strjoin_free("ffffffffffffffff", "", 0));
	if (pr_par->num == (long long)ULONG_MAX && pr_par->type == 'X'
	&& pr_par->length == 'l')
		return (ft_strjoin_free("FFFFFFFFFFFFFFFF", "", 0));
	if (pr_par->num == (long long)ULLONG_MAX && pr_par->type == 'o'
	&& pr_par->length == 'L')
		return (ft_strjoin_free("1777777777777777777777", "", 0));
	if (pr_par->num == (long long)ULLONG_MAX && pr_par->type == 'x'
	&& pr_par->length == 'L')
		return (ft_strjoin_free("ffffffffffffffff", "", 0));
	if (pr_par->num == (long long)ULLONG_MAX && pr_par->type == 'X'
	&& pr_par->length == 'L')
		return (ft_strjoin_free("FFFFFFFFFFFFFFFF", "", 0));
	return (NULL);
}

char	*extra_work(t_print_params *pr_par, char *str)
{
	if (pr_par->precision > 0 || pr_par->align_to_left == 1)
		pr_par->use_zeros = 0;
	if (pr_par->padding_size == 0 || pr_par->padding_size < (int)ft_strlen(str))
		pr_par->padding_size = ft_strlen(str);
	return (str);
}
