#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libft/includes/libft.h"
# include "tokens.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_bool
{
	false,
	true
}			t_bool;

typedef struct s_cmd
{
	char	**cmdline;
	char	*str;
	int		i;
}			t_cmd;

typedef	struct s_envars
{
	char			*key;
	char			*value;
	struct s_envars	*next;
}			t_envars;

typedef struct s_data
{
	t_bool		has_pipe;
	t_cmd		cmd;
	t_envars	*envars_list;
	t_tokens	*token_list;
}			t_data;

//SPLIT
char	**split(char const *s, char c, t_cmd *d);

//CHECK CMD
int		check_cmd(char *str, t_cmd *d, char **envp);

//UTILS
void	exit_func(t_cmd *d);

//ENV
void	do_env(char **envp);
t_envars	*set_envars_list(char **envp);
//void	check_quotes(char **str, t_env *env);

#endif
