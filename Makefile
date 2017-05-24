# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/17 21:11:30 by nlowe             #+#    #+#              #
#    Updated: 2017/05/24 22:22:58 by nlowe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
LIBFT = libft/libft.a

SRC_PATH = src
SRC_NAME = main.c \
			core.c \
			extended_attributes.c \
			lists.c \
			parsing.c \
			options.c \
			print.c \
			long_print.c \
			print_helper.c \
			sort.c \
			sort_helper.c \
			unix.c \
			utility.c \

LIB_PATH = libft
LIB_NAME = ft

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC = gcc
CFLAGS = -Werror -Wall -Wextra
IFLAGS = -Iincludes
LFLAGS = -L./libft -lft

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "[make] ft_ls: Compiling..."
	@$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) -o $@ $^
	@echo "\033[92m----------------------\n|   ft_ls compiled   |\n|       @nlowe       |\n----------------------\033[0m"

$(LIBFT):
	@make -C$(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $^

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_PATH)
	@make clean -C$(LIB_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C$(LIB_PATH)

re: fclean all

.PHONYL: all, clean, fclean, re
