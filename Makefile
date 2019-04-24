NAME = fillit
SRC = srcs/cleaning.c \
	srcs/creation.c  \
	srcs/desk.c \
	srcs/listfunc.c \
	srcs/main.c \
	srcs/reading.c \
	srcs/solving.c \
	srcs/validation.c

OBJ   = $(SRC:.c=.o)

LIB_DIR  = libft/
LIBFT   = libft/libft.a
LIB_INCS  = libft/includes

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(LIBFT):
	make -C $(LIB_DIR)

%.o: %.c $(HEADER) Makefile
	gcc $(FLAGS) -I$(LIB_INCS) -c $< -o $@

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all