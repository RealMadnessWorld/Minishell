# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 18:48:01 by jarsenio          #+#    #+#              #
#    Updated: 2021/03/09 17:13:17 by jarsenio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra

# directories
SRCDIR		= ./srcs/
INCDIR		= ./includes/

SRCS		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
				ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
				ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c \
				ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_atoi.c ft_strdup.c \
				ft_calloc.c  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strtrim.c \
				ft_substr.c ft_strmapi.c ft_itoa.c get_next_line.c \
				ft_error.c find_ext.c check_img_path.c random_num_gen.c \
				gnl_func.c
HEADERS		= ft_printf.h get_next_line.h libft.h

OBJS = $(SRCS:.c=.o)

BONUS		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstclear.c ft_lstdelone.c \
				ft_lstiter.c ft_lstmap.c

BONUS_OBJS	= $(BONUS:.c=.o)

# printf
PRINTF_PATH = ./ft_printf
PRINTF		= ./ft_printf/libftprintf.a
INCPRINTF	= -I ./ft_printf

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADER)
				@make -C $(PRINTF_PATH)
				@ar rcs $(NAME) $(OBJS)
				@echo "LIBFT COMPILED"
				@rm -rf $(OBJDIR)
				@make clean -C $(PRINTF_PATH)
				@$(RM) $(OBJS) $(BONUS_OBJS)
				@rm -f *.o

%.o:$(SRCDIR)/%.c 
				@$(CC) $(CFLAGS) -I $(INCDIR) $(INCPRINTF) -o $@ -c $<
				

clean:
				@rm -rf $(OBJDIR)
				@make clean -C $(PRINTF_PATH)
				@$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
				@$(RM) $(NAME)
				@make fclean -C $(PRINTF_PATH)

re:			fclean $(NAME)

bonus:		$(OBJS) $(BONUS_OBJS)
				@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:		all clean fclean re bonus obj