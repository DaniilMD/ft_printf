NAME = ft_printf

SRC = ft_printf.c option_handlers.c

OBJ = ft_printf.o option_handlers.o

HEADER = ft_printf.h

$(NAME): $(OBJ)
	@make -C libft/
	##@gcc -Wall -Wextra -Werror $(SRC) -o $(NAME) -L libft -lft
	@gcc $(SRC) -o $(NAME) -L libft -lft

%.o:%.c $(HEADER)
	##@gcc -Wall -Wextra -Werror -I . -c $< -o $@
	@gcc -I . -c $< -o $@

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
