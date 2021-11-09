#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libft/includes/libft.h"
# include "tokens.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char			**cmdline;
	char			*str;
	int				i;
	t_tokens		*t;
}			t_cmd;

char		**split(char const *s, char c, t_cmd *d);
int			check_cmd(char *str, t_cmd *d, char **envp);
void		exit_func(t_cmd *d);
void		do_env(char **envp);

int			is_command(char *str);

void		token_creater(t_cmd *d);
void		token_check(t_tokens *t);
t_tokens	*token_lstnew(char *content);
t_tokens	*token_lstlast(t_tokens *lst);
void	token_lstadd_back(t_tokens **lst, t_tokens *new);

#endif
