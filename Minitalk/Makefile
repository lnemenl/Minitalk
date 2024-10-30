# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 13:28:28 by rkhakimu          #+#    #+#              #
#    Updated: 2024/10/30 17:18:01 by rkhakimu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT			= client
NAME_SERVER			= server
NAME_CLIENT_BONUS	= client_bonus
NAME_SERVER_BONUS	= server_bonus

CC					= cc
CFLAGS				= -Wall -Werror -Wextra -I./lib/Libft
LIBFT				= ./lib/Libft/libft.a

SRC_CLIENT			= src/client.c src/handle_error.c
SRC_SERVER			= src/server.c src/handle_error.c
SRC_CLIENT_BONUS	= src/client_bonus.c src/handle_error.c
SRC_SERVER_BONUS	= src/server_bonus.c src/handle_error.c

OBJ_CLIENT			= $(SRC_CLIENT:.c=.o)
OBJ_SERVER			= $(SRC_SERVER:.c=.o)
OBJ_CLIENT_BONUS	= $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS	= $(SRC_SERVER_BONUS:.c=.o)


.PHONY: all clean fclean re bonus libft

all: $(NAME_CLIENT) $(NAME_SERVER)
bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT) -Llib/Libft -lft
	@echo "Compiled CLIENT executable: $(NAME_CLIENT)"

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER) -Llib/Libft -lft
	@echo "Compiled SERVER executable: $(NAME_SERVER)"

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS) -Llib/Libft -lft
	@echo "Compiled CLIENT_BONUS executable: $(NAME_CLIENT_BONUS)"

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) -o $(NAME_SERVER_BONUS) -Llib/Libft -lft
	@echo "Compiled SERVER_BONUS executable: $(NAME_SERVER_BONUS)"

$(LIBFT):
	@$(MAKE) -C ./lib/Libft
	@echo "LIBFT compiled: $(LIBFT)"

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)
	@$(MAKE) -C ./lib/Libft clean
	@echo "Object files removed"

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	@$(MAKE) -C ./lib/Libft fclean
	@echo "Executables and Libft removed"

re: fclean all
