
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
	srcs/print_cols.c\
	srcs/print_cols2.c\
	srcs/print_rows.c\
	srcs/sort.c\
	srcs/sorting_ft.c\
	srcs/useful.c\
	srcs/main.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIB = libft/

LIBFT = -L./libft -lft

LIB_INC = -I libft/includes

INC = -I includes

.PHONY: all

all: $(NAME)

%.o:%.c
	@gcc $(FLAGS) $(INC) $(LIB_INC) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(INC) $(OBJ) $(LIBFT) $(LIB_INC)

$(LIBFT):
	@make -C $(LIB)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all