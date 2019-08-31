NAME = ft_ls

SRC = check.c\
	check2.c\
	delete.c\
	flags.c\
	info.c\
	lst_ft.c\
	lst_ft2.c\
	main_print.c\
	print_attr.c\
	print_attr2.c\
	print_attr3.c\
	print_cols.c\
	print_cols2.c\
	print_rows.c\
	sort.c\
	sorting_ft.c\
	useful.c\
	main.c\
	color.c\
	pizdo.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/libft.a

LIB_INC = ./libft/includes

LIB_DIR = ./libft

.PHONY: all clean fclean

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) -I ./includes -I $(LIB_INC) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) -o $@ $(OBJ) -I . -L./libft -lft -I $(LIB_INC)

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	rm -rf $(OBJ)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)

re:	clean all