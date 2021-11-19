#ifndef MINISHELL_H
# define MINISHELL_H

/****************************\
*		   Includes			 *
\****************************/

# include "./../libft/includes/libft.h"
# include "tokens.h"
# include <readline/readline.h>
# include <readline/history.h>

/****************************\
*		    Structs			 *
\****************************/

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
void		split(char const *str, char c, t_cmd *d);
int			str_quotes_checker(int i, const char *str, int quotes);

/****************************\
*		  	 Tokens			 *
\****************************/
void		token_creater(t_data *d);
void		token_check(t_tokens *t);
t_tokens	*token_lstnew(char *content);
t_tokens	*token_lstlast(t_tokens *lst);
void		token_lstadd_back(t_tokens **lst, t_tokens *new);
int			is_command(char *str);
int			token_str_checker(char **tmp, char *str, int x);
void		re_check_tokens(t_tokens *t);

/****************************\
*		  Validations		 *
\****************************/
void	validations(t_data *d);

/****************************\
*		  Commandline		 *
\****************************/
int			check_cmd(t_data *d, t_tokens *t);

/****************************\
*		  	 Utils			 *
\****************************/
void		exit_func(t_data *d);
void		be_free_my_child(t_tokens *lst);
void		everyone_be_freeee(t_data *d);
void		data_init(t_data *d);
void		delete(t_envars *node);

/****************************\
*		  	  Env			 *
\****************************/
void		do_env(t_envars *lst);
t_envars	*set_envars_list(char **envp);
void		add(t_tokens *old, char *new);
t_envars	*add_node(char **line);
char		**set_line(char *envl);

/****************************\
*		  	  Pwd			 *
\****************************/
void		do_pwd(t_envars *lst);

/****************************\
*		  	  Unset			 *
\****************************/
void		do_unset(t_envars **lst, char *to_unset);
/****************************\
*		  	  Export		 *
\****************************/
void		do_export(t_envars *lst, char *to_add);

/****************************\
*		  	 Echo			 *
\****************************/
void		echo_fun(t_tokens *t);

/****************************\
*		  	Quotes			 *
\****************************/
int			handle_quotes(t_tokens *tkn_lst);
char		*clean_str(char *str, int quotes, e_token *token);
char		*allocate(char *str, int quotes, e_token *token);

/****************************\
*		  	$$$$$$			 *
\****************************/
int			handle_dollar_sign(t_data *data);
char		*expand_dollar(t_data *data, char *str, int start, int end);
char		*find_var(char *str, int start, int end, t_data *data);

/****************************\
*		   Debbuging		 *
\****************************/
int			token_lstsize(t_tokens *lst);
void		printlst(t_tokens *also_tmp);
void		print_dbl(t_data data);

#endif
