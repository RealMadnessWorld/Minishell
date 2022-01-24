/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:02:53 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/24 19:56:55 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	its_redir(t_tokens *t)
{
	t_tokens	*tmp;

	tmp = t;
	while (tmp && tmp->token != e_pipe)
	{
		if (tmp->token == e_smaller || tmp->token == e_bigger
			|| tmp->token == e_double_bigger || tmp->token == e_double_smaller)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	trim_redir(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (*cmd[i] == '<' || *cmd[i] == '>')
		{
			while (cmd[i])
			{
				free(cmd[i]);
				cmd[i] = NULL;
				i++;
			}
			free(cmd[i]);
			cmd[i] = NULL;
			return ;
		}
		i++;
	}
}

static t_exec	*check_cmd(t_data *d, t_tokens *t)
{
	int		i;
	int		invalid;
	t_exec	*x;

	i = 0;
	x = malloc(sizeof(t_exec));
	x->path = t->str;
	x->env = conv_env(d->envars_list);
	x->t = conv_tokens(t);
	if (!(access(t->str, F_OK)))
		return (x);
	while (d->bin_paths[i] != NULL)
	{
		x->path = ft_strjoin_path(d->bin_paths[i], "/", t->str);
		invalid = access(x->path, F_OK);
		if (!invalid)
			return (x);
		free(x->path);
		i++;
	}
	delete_x(x);
	return (NULL);
}

static void	handle_execve_redir(t_data *d, t_tokens *t, t_exec *x)
{
	if (!handle_fd(d, t))
	{
		everyone_be_freeee(d);
		exit(127);
	}
	trim_redir(x->t);
	everyone_be_freeee(d);
	execve(x->path, x->t, x->env);
}

void	execve_handler(t_data *d, t_tokens *t)
{
	t_exec	*x;
	int		i;

	i = 0;
	if (!d->bin_paths || !(ft_strncmp(t->str, "/bin/ls/", 8)))
	{
		print_error(NULL, "No such file or directory\n");
		if (!(ft_strncmp(t->str, "/bin/ls/", 8)) && !everyone_be_freeee(d))
			exit(126);
		exit(127);
	}
	x = check_cmd(d, t);
	if (x == NULL)
	{
		throw_error(t->str, 127);
		everyone_be_freeee(d);
		exit(127);
	}
	if (its_redir(t))
		handle_execve_redir(d, t, x);
	execve(x->path, x->t, x->env);
}
