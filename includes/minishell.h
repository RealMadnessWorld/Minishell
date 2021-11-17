#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libft/includes/libft.h"
# include "tokens.h"
# include <readline/readline.h>
# include <readline/history.h>

/****************************\
*		    Structs			 *
\****************************/

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
	t_tokens	*t;
}			t_data;

/****************************\
*		   Functions		 *
\****************************/

/****************************\
*		  	 Split			 *
\****************************/
void	split(char const *str, char c, t_cmd *d);
int		str_quotes_checker(int i, const char *str, int quotes);

/****************************\
*		  	 Tokens			 *
\****************************/
t_tokens	*token_creater(t_data *d);
void		token_check(t_tokens *t);
t_tokens	*token_lstnew(char *content);
t_tokens	*token_lstlast(t_tokens *lst);
void		token_lstadd_back(t_tokens **lst, t_tokens *new);
int			is_command(char *str);
int			token_str_checker(char **tmp, char *str, int x);
void		re_check_tokens(t_tokens *t);

/****************************\
*		  Commandline		 *
\****************************/
int			check_cmd(char *str, t_data *d, char **envp);

/****************************\
*		  	 Utils			 *
\****************************/
void		exit_func(t_data *d);
void		be_free_my_child(t_tokens *lst);
void		everyone_be_freeee(t_data *d);

/****************************\
*		  	  Env			 *
\****************************/
void		do_env(char **envp);
t_envars	*set_envars_list(char **envp);
void		add(t_tokens *old, char *new);

/****************************\
*		  	Quotes			 *
\****************************/
int		handle_quotes(t_tokens *tkn_lst);
char	*clean_str(char *str, int quotes, e_token *token);
char	*allocate(char *str, int quotes, e_token *token);

/****************************\
*		   Debbuging		 *
\****************************/
int			token_lstsize(t_tokens *lst);
void		printlst(t_tokens *also_tmp);
void		print_dbl(t_data data);


#endif
