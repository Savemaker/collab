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
	srcs/color.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -g

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
	@gcc $(FLAGS) -o $(NAME) $(INC) $(OBJ) $(LIBFT) $(LIB_INC)
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