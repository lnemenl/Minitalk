# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 13:28:28 by rkhakimu          #+#    #+#              #
#    Updated: 2024/10/28 19:13:54 by rkhakimu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I./lib/Libft
LIBFT		= ./lib/Libft/libft.a

SRC_CLIENT  = src/client.c src/handle_error.c
SRC_SERVER  = src/server.c src/handle_error.c
OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)
OBJ_SERVER	= $(SRC_SERVER:.c=.o)

.PHONY: all clean fclean re libft

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT) -Llib/Libft -lft
	@echo "Compiled client executable: $(NAME_CLIENT)"

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER) -Llib/Libft -lft
	@echo "Compiled server executable: $(NAME_SERVER)"

$(LIBFT):
	@$(MAKE) -C ./lib/Libft
	@echo "LIBFT compiled: $(LIBFT)"

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	@$(MAKE) -C ./lib/Libft clean
	@echo "Object files removed"

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@$(MAKE) -C ./lib/Libft fclean
	@echo "Executables and Libft removed"

re: fclean all
