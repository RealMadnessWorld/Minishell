#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

int		split(char const *s, char c, char **save);

#endif