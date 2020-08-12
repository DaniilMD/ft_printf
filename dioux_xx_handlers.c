#include "ft_printf.h"

char	*num_getter(t_print_params *pr_par, va_list args)
{
	char		*str;

	str = NULL;
	if (pr_par->type == 'd' || pr_par->type == 'i')
		length_changer_di(pr_par, args);
	else if (pr_par->type == 'u')
		length_changer_u(pr_par, args);
	else
		length_changer_ox_xx(pr_par, args);
	if (exceptions(pr_par) != NULL)
		return (exceptions(pr_par));
	if (pr_par->type == 'd' || pr_par->type == 'i')
		str = ft_itoa_base(pr_par->num, 10, pr_par);
	else if (pr_par->type == 'u')
		str = ft_itoa_base_uns(pr_par->num_u, 10, pr_par);
	else if (pr_par->type == 'o')
		str = ft_itoa_base(pr_par->num, 8, pr_par);
	else if (pr_par->type == 'x')
		str = ft_itoa_base(pr_par->num, 16, pr_par);
	else if (pr_par->type == 'X')
	{
		pr_par->hex_sym = 'A';
		str = ft_itoa_base(pr_par->num, 16, pr_par);
	}
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
	i = 0;
	pr_par->str_start = str;
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
			if (i < len)
				buff_filler(pr_par, *str++);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
		else
		{
			if (i < pr_par->padding_size - len)
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
			else
				buff_filler(pr_par, *str++);
		}
		i++;
	}
}

void	oux_xx_handler(t_print_params *pr_par, va_list args)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	str = num_getter(pr_par, args);
	str = extra_work(pr_par, str);
	len = ft_strlen(str);
	pr_par->str_start = str;
	while (i < pr_par->padding_size)
	{
		if (pr_par->align_to_left == 1)
			if (i < len)
				buff_filler(pr_par, *str++);
			else
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
		else
		{
			if (i < pr_par->padding_size - len)
				buff_filler(pr_par, (pr_par->use_zeros == 1) ? '0' : ' ');
			else
				buff_filler(pr_par, *str++);
		}
		i++;
	}
}

char	*ft_strjoin_free(char *s1, char *s2, int indic)
{
	int		len;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = ft_strnew(len + 1);
	if (!tmp)
		return (NULL);
	ft_strcat(tmp, (char*)s1);
	ft_strcat(tmp, (char*)s2);
	if (indic == 1)
		if (s1 != NULL)
			free(s1);
	if (indic == 2)
		if (s2 != NULL)
			free(s2);
	if (indic == 3)
		if (s1 != NULL && s2 != NULL)
		{
			free(s1);
			free(s2);
		}
	return (tmp);
}
