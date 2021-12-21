#include "../../includes/minishell.h"

int	only_redirs(t_tokens *t)
{
	t_tokens	*curr;

	curr = t;
	while (curr && curr->token != e_pipe)
	{
		if (curr->token != e_smaller && curr->token != e_bigger &&
			curr->token != e_double_bigger && curr->token != e_double_smaller &&
			curr->token != e_fd)
			return (0);
		curr = curr->next;
	}
	return (1);
}

static int	exec_cmd(t_data *d, t_tokens *t)
{
	pid_t	pid;
	int		status;

	if (only_redirs(t))
	{
		handle_fd(d, t);
		return (1);
	}
	if (t->token == e_command)
	{
		g_status = do_builtin(d, t);
		restart_fd(d);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execve_handler(d, t);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
       			g_status = WEXITSTATUS(status);
		}
	}
	return (g_status);
}

static int	exec_piped_cmd(t_data *d, t_tokens *t, int pipe_pos)
{
	t_exec	*x;
	pid_t	pid;
	int		status;
	int		ret;

	x = NULL;
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
		g_status = (WEXITSTATUS(status) / 256);
	return (g_status);
}

void do_pipes(t_tokens **cmd_array, int nr_pipes, t_data *d)
{
	int	i;

	i = -1;
	if (nr_pipes == 1)
	{
		while (++i <= nr_pipes)
		{
			if (only_redirs(cmd_array[i]))
			{
				handle_fd(d, cmd_array[i]);
				continue ;
			}
			g_status = exec_piped_cmd(d, cmd_array[i], i);
		}
	}
	else
	{
		while (++i < (nr_pipes + 1))
		{
			if (only_redirs(cmd_array[i]))
			{
				handle_fd(d, cmd_array[i]);
				continue ;
			}
			g_status =  exec_piped_cmd(d, cmd_array[i], i);
		}
	}
	unlink(".heredoc");
}

void	executor(t_data *d, t_tokens *t)
{
	int			i;
	t_tokens	**cmd_array;

	i = -1;
	d->bin_paths = ft_split(get_env(d->envars_list, "PATH"), ':');
	d->nr_pipes = count_pipes(t);
	cmd_array = NULL;
	if (!commands_tokens(t))
		return ;
	if (d->nr_pipes > 0)
	{
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
	}
	else
		exec_cmd(d, t);
}
