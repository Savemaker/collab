NAME = ft_ls

SRC = ft_ls.c checking.c flags.c lst.c sorting.c printing.c column_output.c row_output.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIB	= libft/

LIBFT = -L./libft -lft

LIB_INC = -I libft/includes

.PHONY: all

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) -I ft_ls.h $(LIB_INC) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) -o $(NAME) -I ft_ls.h $(OBJ) $(LIBFT) $(LIB_INC)

$(LIBFT):
	make -C $(LIB)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all