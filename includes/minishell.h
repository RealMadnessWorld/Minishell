#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char	**cmdline;
	int		i;
}			t_cmd;

t_cmd *go;

char	**split(char const *s, char c, t_cmd *d);
int		check_cmd(char *str, t_cmd *d);
void	exit_func(t_cmd *d);


#endif