
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <math.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct	s_print_params
{
	int			curr_i;
	int			print_sign;
	int			use_zeros;
	int			align_to_left;
	int			space_option;
	int			alt_format;
	int			padding_size;
	int			precision;
	char		length;
	char		type;
	int			buff_cntr;
	char		*printf_buf;
	const char	*str;
	char		hex_sym;
	int			prec_indic;
}				t_print_params;

/*
** ft_printf.c
*/

void			options_handler(t_print_params *pr_par, va_list args);
int				just_printer(char *printf_buf, const char *str, va_list args);
int				ft_printf(const char *format, ...);


/*
** option_handlers.c
*/

void			flags_handler(t_print_params *pr_par);
void			width_handler(t_print_params *pr_par, va_list args);
void			precision_handler(t_print_params *pr_par, va_list args);
void			length_handler(t_print_params *pr_par);
void			type_handler(t_print_params *pr_par);

/*
** csp_handlers.c
*/

void			c_handler(t_print_params *pr_par, va_list args);
void			s_handler(t_print_params *pr_par, va_list args);
void			p_handler(t_print_params *pr_par, va_list args);

/*
** support_functions.c
*/

void			buff_filler(t_print_params *pr_par, int sym);
char			*ft_itoa_base(long long n, int base, t_print_params *pr_par);
char			*ft_itoa_option(char *str, t_print_params *pr_par, int sign, long long n);

//char			*ft_itoa_option(char *str, char option, int sign);
//char			*ft_itoa_base(long long n, int base, char option, char x);

/*
** diouxX_handlers.c
*/

long long		length_changer(t_print_params *pr_par, va_list args);
char			*num_getter(t_print_params *pr_par, va_list args);
char			*extra_work(t_print_params *pr_par, char *str);
void			di_handler(t_print_params *pr_par, va_list args);
void			ouxX_handler(t_print_params *pr_par, va_list args);


#endif
