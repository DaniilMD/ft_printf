
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
	int			length;
	char		type;
	int			buff_cntr;
	char		*printf_buf;
	const char	*str;
	va_list		args;
}				t_print_params;

/*
** ft_printf.c
*/


/*
** option_handlers.c
*/

void	flags_handler(t_print_params *pr_par, va_list args);
void	width_handler(t_print_params *pr_par, va_list args);
void	precision_handler(t_print_params *pr_par, va_list args);
void	length_handler(t_print_params *pr_par, va_list args);
void	type_handler(t_print_params *pr_par, va_list args);

/*
**
*/



/*
**
*/

#endif
