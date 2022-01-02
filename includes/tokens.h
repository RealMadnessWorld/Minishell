/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 17:08:29 by fmeira            #+#    #+#             */
/*   Updated: 2021/12/30 18:14:42 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "minishell.h"

typedef enum s_token
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
	e_fd,
	is_nothing
}			t_token;

typedef struct s_tokens
{
	char			*str;
	t_token			token;
	struct s_tokens	*next;
}			t_tokens;

#endif
