/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:02:16 by fmeira            #+#    #+#             */
/*   Updated: 2021/12/30 19:43:34 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_pipes(t_tokens **cmd_array, int nr_pipes, t_data *d)
{
	int	i;

	i = -1;
	if (nr_pipes == 1)
	{
		while (++i <= nr_pipes)
			exec_pipe(cmd_array[i], d, i);
	}
	else
	{
		while (++i < (nr_pipes + 1))
			exec_pipe(cmd_array[i], d, i);
	}
	unlink(".heredoc");
}

void	manage_input_output(int nr_pipes, int **pipe_fd, int pipe_pos)
{
	if (pipe_pos == 0)
	{
		close(pipe_fd[0][0]);
		dup2(pipe_fd[0][1], STDOUT_FILENO);
		close(pipe_fd[0][1]);
	}
	else if (nr_pipes > 1 && pipe_pos > 0 && pipe_pos < nr_pipes)
	{
		close(pipe_fd[pipe_pos][0]);
		dup2(pipe_fd[pipe_pos - 1][0], STDIN_FILENO);
		close(pipe_fd[pipe_pos - 1][0]);
		dup2(pipe_fd[pipe_pos][1], STDOUT_FILENO);
		close(pipe_fd[pipe_pos][1]);
	}
	else if (pipe_pos == nr_pipes)
	{
		dup2(pipe_fd[pipe_pos - 1][0], STDIN_FILENO);
		close(pipe_fd[pipe_pos - 1][0]);
	}
}

void	close_pipes(int nr_pipes, int **pipe_fd, int pipe_pos)
{
	if (pipe_pos == 0)
	{
		if (close (pipe_fd[pipe_pos][1]) == -1)
			perror("close 1");
	}
	else if (nr_pipes > 1 && pipe_pos > 0 && pipe_pos < nr_pipes)
	{
		if (close(pipe_fd[pipe_pos][1]) == -1)
			perror("close 2");
	}
	else if (pipe_pos == nr_pipes)
	{
		if (close(pipe_fd[pipe_pos - 1][0]) == -1)
			perror("close 3");
	}
}

static int	exec_piped_cmd(t_data *d, t_tokens *t, int pipe_pos)
{
	pid_t	pid;
	int		status;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		manage_input_output(d->nr_pipes, d->pipes, pipe_pos);
		if (t->token == e_command)
		{
			ret = do_builtin(d, t);
			restart_fd(d);
			exit(ret * 256);
		}
		else
			execve_handler(d, t);
		exit(1);
	}
	waitpid(pid, &status, 0);
	close_pipes(d->nr_pipes, d->pipes, pipe_pos);
	if (WIFEXITED(status))
		g_g.status = (WEXITSTATUS(status) / 256);
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (g_g.status);
}

void	exec_pipe(t_tokens *cmd, t_data *d, int i)
{
	if (only_redirs(cmd))
	{
		handle_fd(d, cmd);
		restart_fd(d);
		return ;
	}
	g_g.status = exec_piped_cmd(d, cmd, i);
}
