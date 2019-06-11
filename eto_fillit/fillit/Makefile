# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 18:23:54 by gbeqqo            #+#    #+#              #
#    Updated: 2019/03/24 18:12:36 by gbeqqo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = ./srcs/main.c ./srcs/reading.c ./srcs/listfunc.c ./srcs/solving.c ./srcs/ft_memmove.c \
	./srcs/ft_strdup.c ./srcs/editing.c ./srcs/validation.c ./srcs/placing.c

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