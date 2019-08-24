NAME = ft_ls

SRC = srcs/check.c\
        srcs/check2.c\
        srcs/delete.c\
        srcs/flags.c\
        srcs/info.c\
        srcs/lst_ft.c\
        srcs/lst_ft2.c\
        srcs/main_print.c\
	srcs/print_attr.c\
        srcs/print_attr2.c\
        srcs/print_attr3.c\
        srcs/print_cols.c\
        srcs/print_cols2.c\
        srcs/print_rows.c\
        srcs/sort.c\
        srcs/sorting_ft.c\
        srcs/useful.c\
        srcs/color.c\
        srcs/pizdo.c\

INCLUDES = includes

FLAGS = -Wall -Wextra -Werror -g

LIB = libft

LIBINC = libft/includes

all: $(NAME)

$(NAME):
			@echo "Сompilation $(NAME)"			
			@make re -C $(LIB)
			@gcc $(FLAGS) -o $(NAME) main.c $(SRC) -I libft/includes -I $(INCLUDES) -L./libft -lft
			@echo "I ♥ bacon"

clean:
			@echo "Clean object files"			
			@make clean -C $(LIB)

fclean: clean
			@echo "Clean $(NAME)"
			@make fclean -C $(LIB)
			@rm -f $(NAME)

re: fclean all