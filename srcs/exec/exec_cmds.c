/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:00:05 by fmeira            #+#    #+#             */
/*   Updated: 2021/12/30 20:21:34 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	only_redirs(t_tokens *t)
{
	t_tokens	*curr;

	curr = t;
	while (curr && curr->token != e_pipe)
	{
		if (curr->token != e_smaller && curr->token != e_bigger
			&& curr->token != e_double_bigger && curr->token != e_double_smaller
			&& curr->token != e_fd)
			return (0);
		curr = curr->next;
	}
	return (1);
}

int	count_pipes(t_tokens *t)
{
	t_tokens	*curr;
	int			i;

	curr = t;
	i = 0;
	while (curr)
	{
		if (curr->token == e_pipe)
			i++;
		curr = curr->next;
	}
	return (i);
}

static void	execute_child_labor(t_data *d, t_tokens *t)
{
	pid_t	pid;
	int		status;

	g_g.child = 1;
	pid = fork();
	if (pid == 0)
		execve_handler(d, t);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_g.status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_g.status = (128 + WTERMSIG(status));
	}
}

int	exec_cmd(t_data *d, t_tokens *t)
{
	if (only_redirs(t))
	{
		set_fd_names(d, t);
		restart_fd(d);
		return (1);
	}
	else if (t->token == e_command)
	{
		g_g.status = do_builtin(d, t);
		restart_fd(d);
	}
	else
		execute_child_labor(d, t);
	return (g_g.status);
}

void	ft_pipes(t_data *d, t_tokens *t)
{
	int			i;
	t_tokens	**cmd_array;

	i = -1;
	cmd_array = conv_cmds(t, d->nr_pipes);
	d->pipes = malloc(sizeof(int *) * (d->nr_pipes + 1));
	while (++i < d->nr_pipes)
	{
		d->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(d->pipes[i]) == -1)
			perror("pipe");
	}
	d->pipes[i] = NULL;
	do_pipes(cmd_array, d->nr_pipes, d);
	free_pipes(d);
	free(cmd_array);
	cmd_array = NULL;
}
