# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:26:17 by rkhakimu          #+#    #+#              #
#    Updated: 2024/09/05 15:34:06 by rkhakimu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = pipex

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

AR = ar rcs

RM = rm -rf

SRC =

OBJ =

LIBFT = ./Libft

all: $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) Libft/libft.a -o $(NAME)

clean:
	@make -C ./Libft clean
	$(RM) $(OBJ)

fclean: clean
	@make -C ./Libft fclean
	$(RM) $(NAME)

re: fclean all