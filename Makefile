# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                                                  #
#                                                     +:+ +:+         +:+      #
#    By: glavigno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/19 12:48:50 by glavigno          #+#    #+#              #
#    Updated: 2018/11/28 20:05:00 by apeyret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a 

SRC =	ft_printf.c \
		parsing.c \
		pf_itoa.c

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I libft/

OBJ = $(SRC:.c=.o)


all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "█"

prcompil:
	@printf "\x1B[32m[Printf] Compilation:\n"

$(NAME): prcompil $(OBJ)
	@printf "\n"
	@make -C libft/
	@$(CC) $(CFLAGS) $(INC) -o $@ $^ 

clean:
	@make clean -C libft/
	@/bin/rm -f $(OBJ)
	@printf "\033[0;31m[Printf] Deleted *.o\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@make nofclean -C libft/
	@printf "\033[0;31D[Printf] Deleted ft_printf.a\n"

re: fclean all

.PHONY: all clean fclean re