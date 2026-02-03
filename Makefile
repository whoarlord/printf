# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/29 12:40:51 by iarrien-          #+#    #+#              #
#    Updated: 2026/02/02 17:59:25 by iarrien-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=a.out

CC=cc
CFLAGS= -Wall -Werror -Wextra -I. -g
LIB= libftprintf.a

SRC=ft_printf.c  ft_print_formats.c  ft_print_ptr.c  ft_print_str.c ft_print_nbr.c ft_print_unnbr.c ft_print_hex.c
OBJ=$(SRC:.c=.o)
HEADERS=./libft/libft.h ft_printf.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(MAKE) -C ./libft
	cp ./libft/libft.a $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C ./libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re makelibft