#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libft/includes/libft.h"
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

typedef	struct s_elist
{
	char			*key;
	char			*value;
	struct s_elist	*next;
}			t_elist;

typedef struct s_data
{
	t_bool	has_pipe;
	t_cmd	cmd;
	t_elist *env_list;
}			t_data;

t_cmd *go;

char	**split(char const *s, char c, t_cmd *d);
int		check_cmd(char *str, t_cmd *d, char **envp);
void	exit_func(t_cmd *d);
void	do_env(char **envp);
//void	check_quotes(char **str, t_env *env);
t_elist	*set_env_list(char **envp);


#endif
