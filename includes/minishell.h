#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char	**cmdline;
	char	*str;
	int		i;
}			t_cmd;

t_cmd *go;

char	**split(char const *s, char c, t_cmd *d);
int		check_cmd(char *str, t_cmd *d, char **envp);
void	exit_func(t_cmd *d);
void	do_env(char **envp);

#endif
