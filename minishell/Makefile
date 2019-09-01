#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/11 16:08:29 by bellyn-t          #+#    #+#              #
#    Updated: 2019/08/11 16:30:34 by bellyn-t         ###   ########.fr        #
#                                                                              #
#******************************************************************************#
NAME = minishell

SRC = srcs/main.c\
        srcs/setenv.c\
        srcs/unsetenv.c\
        srcs/builtin.c\
        srcs/error.c\
        srcs/split.c\


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
	@echo "Сompilation $(NAME)"
	@gcc $(FLAGS) -o $(NAME) $(INC) $(OBJ) $(LIBFT) $(LIB_INC) -lreadline -ledit
	@echo "I ♥ bacon"

$(LIBFT):
	@make re -C $(LIB)

clean:
	@echo "Clean object files"	
	@rm -rf $(OBJ)
	@make clean -C $(LIB)

fclean: clean
	@echo "Clean $(NAME)"
	@rm -rf $(NAME)
	@make re -C $(LIB)

re: fclean all