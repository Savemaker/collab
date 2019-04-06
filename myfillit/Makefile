NAME = fillit

SRC = ./srcs/main.c ./srcs/reading.c ./srcs/listfunc.c ./srcs/lib.c ./srcs/slavastrdup.c \
	./srcs/validation.c

OBJ = $(SRC:.c=.o)

HEADER = ../includes/fillit.h

all:	&(NAME)

&(NAME): $(OBJ)
	gcc -Wall -Werror -Wextra -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all
