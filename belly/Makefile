NAME = minishell

SRC = builtin.c error.c  main.c setenv.c split.c  unsetenv.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/libft.a

LIB_INC = ./libft/includes

LIB_DIR = ./libft

GREEN = \033[0;32m

.PHONY: all clean fclean

all: $(NAME)

%.o:%.c
	@gcc $(FLAGS) -I ./includes -I $(LIB_INC) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(FLAGS) -o $@ $(OBJ) -I . -L./libft -lft -I $(LIB_INC) -lreadline -ledit
	@echo "$(GREEN)Co︎mpiled $(NAME) successfully!"
$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@echo "Clean object files"
	@rm -rf $(OBJ)
	@make clean -C $(LIB_DIR)

fclean: clean
	@echo "Clean $(NAME)"	
	@rm -rf $(NAME)
	@make fclean -C $(LIB_DIR)

re:	clean all