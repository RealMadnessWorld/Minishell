#ifndef MINISHELL_H
# define MINISHELL_H

/****************************\
*		   Includes			 *
\****************************/

# include "./../libft/includes/libft.h"
# include "tokens.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

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

typedef struct s_exec
{
	char			**env;
	char			**t;
	char			*path;
}			t_exec;

typedef struct s_fd
{
	char			*in_name;
	int				in;
	int				in_original;
	char			*out_name;
	int				out;
	int				out_original;
	int				weirdoc;
	int				heredoc_count;
	int				heredoc_fd;
	int				append;
	int				i_out;
	int				i_in;
}			t_fd;

typedef struct s_data
{
	t_cmd			cmd;
	t_envars		*envars_list;
	t_tokens		*t;
	t_exec			*exec;
	t_fd			fd;
	char			**bin_paths;
	int				env_size;
	int				nr_pipes;
	int				**pipes;
}			t_data;

int	g_status;

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
int			token_creater(t_data *d);
void		token_check(t_tokens *t);
t_tokens	*token_lstnew(char *content);
t_tokens	*token_lstlast(t_tokens *lst);
void		token_lstadd_back(t_tokens **lst, t_tokens *new);
int			is_command(char *str);
int			token_str_checker(char **tmp, char *str, int x);
void		re_check_tokens(t_tokens *t);
void		check_vars(t_tokens *t);
int			commands_tokens(t_tokens *t);
int			cd_parser(t_tokens *t);
int			echo_parser(t_tokens *t);
int			set_fd(t_tokens *tmp);

/****************************\
*			Execute			 *
\****************************/
void		executor(t_data *d, t_tokens *t);
void		execve_handler(t_data *d, t_tokens *t);

/****************************\
*		  Commandline		 *
\****************************/
int			do_builtin(t_data *d, t_tokens *t);

/****************************\
*		  Pipes				 *
\****************************/
void		manage_input_output(int nr_pipes, int **pipe_fd, int pipe_pos);
void		close_pipes(int nr_pipes, int **pipe_fd, int pipe_pos);
int			count_pipes(t_tokens *t);
void		pipe_error(char *str);
int			only_redir(t_data *d, t_tokens *t);

/****************************\
*		  Redirections		 *
\****************************/
int			set_fd_names(t_data *d, t_tokens *t);
int			open_fd(t_data *d);
void		restart_fd(t_data *d);
int			check_fd_already_redin(t_data *d);
int			check_fd_already_redout(t_data *d);
int			check_fd_already_append(t_data *d);
int			handle_fd(t_data *d, t_tokens *t);
int			do_red_append(t_data *d, t_tokens *tmp);
int			do_red_weirdoc(t_data *d, t_tokens *tmp);
int			do_red_bigger(t_data *d, t_tokens *tmp);
int			do_red_smaller(t_data *d, t_tokens *tmp);
int			choose_out(t_data *d);
int			choose_in(t_data *d);
void		close_start_fd(t_data *d);

/****************************\
*			 Utils			 *
\****************************/
void		delete(t_envars *node);
int			error_zero(char *error);
void		do_i_have_signal();
char		**conv_tokens(t_tokens *t);
char		**conv_env(t_envars *t);
t_tokens	**conv_cmds(t_tokens *t, int nr_pipes);
int			env_lstsize(t_envars *lst);
void		order(t_envars *t);
int			ordered(t_envars *t);
void		print_export(t_envars *t);
t_envars	*env_last(t_envars *t);
t_envars	*env_new(char *key, char *value);
void		env_add_lst(t_envars **t, t_envars *new);
int			redirections_tokens(t_tokens *t);
int			throw_error(char *str, int err);

/****************************\
*		  	 Free			 *
\****************************/
void		be_free_my_child(t_tokens *lst);
int			everyone_be_freeee(t_data *d);
void		free_envars_list(t_envars *env);
void		free_pipes(t_data *d);

/****************************\
*		  	  Env			 *
\****************************/

void		env_print(t_data *data);
void		parse_envars(t_tokens *tkn_lst, t_envars *envars_lst);
void		add_envar(char *str, t_envars *envars_lst);
t_envars	*set_envars_list(char **envp);
void		add(t_tokens *old, char *new);
t_envars	*add_node(char **line);
char		**set_line(char *envl);
char		*get_env(t_envars *env, char *str);
void		set_env(t_envars *env, char *key, char *value);

/****************************\
*		  	  Builtins		 *
\****************************/
int			do_env(t_envars *lst);
void		exit_func(t_data *d, t_tokens *t);
int			do_pwd(void);
int			unset_func(t_envars **env, t_tokens *t);
int			do_export(t_envars *lst, char *to_add);
int			export_func(t_envars *lst, t_tokens *t);
int			echo_fun(t_tokens *t);
int			do_cd(t_tokens *tkn_lst, t_envars *env);

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
