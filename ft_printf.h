#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdarg.h>
# include <limits.h>

typedef struct			s_print_params
{
	int					curr_i;
	int					print_sign;
	int					use_zeros;
	int					align_to_left;
	int					space_option;
	int					alt_format;
	int					padding_size;
	int					precision;
	char				length;
	char				type;
	int					buff_cntr;
	char				*printf_buf;
	const char			*str;
	char				hex_sym;
	int					prec_indic;
	long long			num;
	unsigned long long	num_u;
	char				*str_start;
}						t_print_params;

/*
** ft_printf.c
*/

void					init_pr_par(t_print_params *pr_par);
void					param_zeroer(t_print_params *pr_par);
void					options_handler(t_print_params *pr_par, va_list args);
int						just_printer(char *printf_buf,
	const char *str, va_list args);
int						ft_printf(const char *format, ...);

/*
** option_handlers.c
*/

void					flags_handler(t_print_params *pr_par);
void					width_handler(t_print_params *pr_par, va_list args);
void					precision_handler(t_print_params *pr_par, va_list args);
void					length_handler(t_print_params *pr_par);
void					type_handler(t_print_params *pr_par);

/*
** csp_per_handlers.c
*/

void					csp_params_changer(t_print_params *pr_par, char *str);
void					c_handler(t_print_params *pr_par, va_list args);
void					s_handler(t_print_params *pr_par, va_list args);
void					p_handler(t_print_params *pr_par, va_list args);
void					percent_handler(t_print_params *pr_par);

/*
** support_functions.c
*/

void					buff_filler(t_print_params *pr_par, int sym);
char					*itoa_option_help(char *str,
	t_print_params *pr_par, int is_zero);
char					*ft_itoa_option(char *str,
	t_print_params *pr_par, int sign, int is_zero);
char					*ft_itoa_base(long long n, int base,
	t_print_params *pr_par);
char					*ft_itoa_base_uns(unsigned long long n, int base,
	t_print_params *pr_par);

/*
** dioux_xx_handlers.c (and ft_strjoin_free)
*/

char					*ft_strjoin_free(char *s1, char *s2, int indic);

char					*num_getter(t_print_params *pr_par, va_list args);
void					di_handler(t_print_params *pr_par, va_list args);
void					oux_xx_handler(t_print_params *pr_par, va_list args);

/*
** dioux_xx_helpers.c
*/

void					length_changer_di(t_print_params *pr_par, va_list args);
void					length_changer_u(t_print_params *pr_par, va_list args);
void					length_changer_ox_xx(t_print_params *pr_par,
	va_list args);
char					*exceptions(t_print_params *pr_par);
char					*extra_work(t_print_params *pr_par, char *str);

/*
** f_handler.c
*/

int						f_pow(int num, int grade);
void					f_printer(t_print_params *pr_par, char *str);
char					*f_str_filler(t_print_params *pr_par,
	long double f_part, char *str);
void					f_handler(t_print_params *pr_par, va_list args);

#endif
