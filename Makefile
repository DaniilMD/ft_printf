
NAME =  libftprintf.a

SRC = ft_printf.c option_handlers.c csp_per_handlers.c \
support_functions.c dioux_xx_handlers.c dioux_xx_helpers.c f_handler.c

OBJ = $(SRC:.c=.o)

HEADER = ft_printf.h

$(NAME): $(OBJ)
	@make -C libft/
	@cp ./libft/libft.a $(NAME)
	@ar rc $(NAME) $(OBJ)

%.o:%.c $(HEADER)
	@gcc -Wall -Wextra -Werror -I . -c $< -o $@

clean:
	@/bin/rm -f *~
	@/bin/rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

all: $(NAME)

re: fclean all

.PHONY: clean fclean all re