#ifndef TOKENS_H
# define TOKENS_H

# include "minishell.h"
# include "structs.h"

typedef enum	s_token
{
	e_command,
	e_pipe,
	e_quotes,
	e_single_quotes,
	e_bigger,
	e_smaller,
	e_or,
	e_and,
	e_var,
	e_double_bigger,
	e_double_smaller,
	e_n_flag,
	e_echo_print,
	e_cd_path,
	is_nothing
}			e_token;

typedef struct	s_tokens
{
	char			*str;
	e_token			token;
	struct s_tokens	*next;
}			t_tokens;

#endif
