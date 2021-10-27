# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/02 15:53:49 by jarsenio          #+#    #+#              #
#    Updated: 2021/04/22 10:14:23 by jarsenio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f
NAME        = libftprintf.a
INCLUDE     = ft_printf.h
SRCS        = ft_printf.c ft_charconv.c ft_check.c ft_hexaconv.c ft_intconv.c ft_itoa.c \
				ft_pointconv.c ft_printers.c ft_unsigconv.c ft_utils.c ft_width.c
OBJS        = $(SRCS:.c=.o)
all:        $(NAME)
$(NAME):    $(OBJS) $(INCLUDE)
			@ar -rcs $(NAME) $(OBJS)
			@echo "PRINTF COMPILED"

bonus:		all

.c.o:
			@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
clean:
			@$(RM) $(OBJS)
fclean:     clean
			@$(RM) $(NAME)
re:         fclean all
test: $(OBJS) $(INCLUDE)
			@${CC} $(OBJS) -o test
.PHONY:     all clean fclean re bonus