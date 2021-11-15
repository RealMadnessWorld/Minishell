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
	char			**cmdline;
	char			*str;
	int				i;
	t_tokens		*t;
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
void	split(char const *str, char c, t_cmd *d);
int		str_quotes_checker(int i, const char *str, int quotes);

//TOKENS
t_tokens	*token_creater(t_cmd *d);
void		token_check(t_tokens *t);
t_tokens	*token_lstnew(char *content);
t_tokens	*token_lstlast(t_tokens *lst);
void		token_lstadd_back(t_tokens **lst, t_tokens *new);
int			is_command(char *str);
int			token_str_checker(char **tmp, char *str, int x);

//CHECK CMD
int			check_cmd(char *str, t_data *d, char **envp);

//UTILS
void		exit_func(t_data *d);
void		be_free_my_child(t_tokens *lst);
void		everyone_be_freeee(t_data *d);

//ENV
void		do_env(char **envp);
t_envars	*set_envars_list(char **envp);
//void		check_quotes(char **str, t_env *env);

//DEBUG
int			token_lstsize(t_tokens *lst);

#endif
