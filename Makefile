# -*- MakeFile -*-
OS			= $(shell uname)

MAKEFLAGS	+= -s

CPPFLAGS	= -I ~/.brew/opt/readline/include
CFLAGS		= $(CPPFLAGS) -Wall -Werror -Wextra -g #-fsanitize=address

NAME		= minishell

INCDIR		= ./includes/

LIBFT_DIR	= ./libft/
LIBFT_EXEC	= libft/libft.a
LIB_INC		= -I ./includes/libft

SRCS		= ${wildcard srcs/*.c}
SRCS		+= ${wildcard srcs/*/*.c}
OBJS		= $(SRCS:.c=.o)

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

.o: .c
	gcc $(CFLAGS) -c $< -o $@ -L ~/.brew/opt/readline/lib -lreadline

all: $(NAME)

$(NAME): $(LIBFT_EXEC) $(OBJS)
	gcc -o $(NAME) $(CFLAGS) -I $(INCDIR) $(OBJS) $(LIBFT_EXEC) -L ~/.brew/opt/readline/lib -lreadline
	mkdir -p objs
	mv ${OBJS} objs
	echo "$(_GREEN)Compilation complete mothafuckaaaaaaaaaaaaaaaa!!!!!!$(_RESET)"

$(LIBFT_EXEC):
	@${MAKE} -C $(LIBFT_DIR)

debug:
	gcc -o $(NAME) $(CFLAGS) -I $(INCDIR) $(OBJS) debug $(LIBFT_EXEC) -L ~/.brew/opt/readline/lib -lreadline

nowarn: $(LIBFT_EXEC) $(OBJS)
	gcc -w $(LIBFT_EXEC) $(OBJS) -I $(INCDIR) $(LIB_INC) -o $(NAME) -lreadline
	mkdir -p objs
	mv ${OBJS} objs
	echo "$(_GREEN)Compilation without warnings complete mothafuckaaaaaaa!!!!!!$(_RESET)"

clean:
	rm -rf objs ${OBJS}
	${MAKE} -C $(LIBFT_DIR) clean
	echo "$(_YELLOW)Taste my lightning fuckers!!!!⚡⚡⚡$(_RESET)"

fclean:
	rm -rf objs ${OBJS} $(NAME)
	@${MAKE} -C $(LIBFT_DIR) fclean
	echo "$(_RED)NOOOOOOOOOOOOOOOOOOOOOOOOO!!!!!!!!!!!!$(_RESET)"

dclean:
	rm -rf obj ${OBJS} debug debug.dSYM
	echo "debug and objects cleaned"

re: fclean all

.PHONY: all debug nowarn clean fclean dclean re
