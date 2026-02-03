# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/29 12:40:51 by iarrien-          #+#    #+#              #
#    Updated: 2026/02/03 16:39:07 by iarrien-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

CC=cc
CFLAGS= -Wall -Werror -Wextra -I.
LIB= ar rcs

SRC=ft_printf.c  ft_print_formats.c  ft_print_ptr.c  ft_print_str.c ft_print_nbr.c ft_print_unnbr.c ft_print_hex.c ft_print_chr.c
OBJ=$(SRC:.c=.o)
HEADERS=./libft/libft.h ft_printf.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(MAKE) -C ./libft
	cp ./libft/libft.a $(NAME)
	$(LIB) $(NAME) $(OBJ)

bonus: $(NAME)

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