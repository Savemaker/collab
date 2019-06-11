NAME = fillit

SRC = ./srcs/*.c

OBJ = $(SRC:.c=.o)

HEADER = ./includes/fillit.h

LIB_NAME = libft

LIB_HEADER = ./libft/libft.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -I $(LIB_HEADER) -c $(SRC)
	make -C $(LIB_NAME) re
	gcc $(FLAGS) -I $(HEADER) $(SRC) -L $(LIB_NAME) -lft -o $(NAME)

clean:
	#make clean -C $(LIB_NAME)
	rm -f $(OBJ)

fclean: clean
	#make -C $(LIB_NAME) fclean
	rm -f $(NAME)

re:	fclean all
