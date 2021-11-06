NAME	= minishell

OS		= $(shell uname)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

# directories
SRCDIR	= ./srcs/
INCDIR	= ./includes/
OBJDIR	= ./objs/

# files
SRCS	= minishell.c split.c utils.c check_cmd.c
HEADER	= minishell.h tokens.h
OBJ		= $((addprefix $(OBJDIR)/,SRCS:.c=.o))

# libft
LIBFT	= ./libft/libft.a
LIB_INC	= -I ./includes/libft

ifeq ($(OS), Linux)
		_RED	= \e[31;5;184m
		_GREEN	= \e[38;5;46m
		_YELLOW	= \e[38;5;184m
		_RESET	= \e[0m
else
		_RED	= \x1b[31m
		_GREEN	= \x1b[32m
		_YELLOW	= \x1b[33m
		_RESET	= \x1b[0m
endif

all:	obj $(LIBFT) $(NAME)

obj:
			@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
			@$(CC) $(CFLAGS) -I $(INCDIR) $(LIB_INC) -o $@ -c $<

$(LIBFT):
			@$(MAKE) bonus -C libft

$(NAME):	$(OBJ)
			@$(CC) -o $(NAME) $(CFLAGS) $(addprefix $(SRCDIR),$(SRCS)) -I $(INCDIR) $(OBJ) $(LIBFT) -lreadline
			@echo "$(_GREEN)Compilation complete mothfockaaaaaaaaaaaaaaaa!!!!!!$(_RESET)"

clean:
			@$(RM) $(OBJDIR)
			@$(MAKE) clean -C libft
			@echo "$(_YELLOW)Taste my lightning fuckers!!!!⚡⚡⚡$(_RESET)"

fclean:	clean
			@$(RM) $(NAME)
			@$(MAKE) fclean -C libft
			@echo "$(_RED)NOOOOOOOOOOOOOOOOOOOOOOOOO!!!!!!!!!!!!$(_RESET)"

re: fclean all

.PHONY: all, clean, fclean, re, obj