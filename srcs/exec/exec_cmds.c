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
			{
			return (0);
			}
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
		set_fd_names(d, t);
		restart_fd(d);
		return (1);
	}
	if (t->token == e_command)
	{
		g.g_status = do_builtin(d, t);
		restart_fd(d);
	}
	else
	{
		g.child = 1;
		pid = fork();
		if (pid == 0)
			execve_handler(d, t);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
       			g.g_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				printf("entered!\n");
				g.g_status = (128 + WTERMSIG(status));
				return (128 + WTERMSIG(status));
			}
		}
	}
	return (g.g_status);
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
		g.g_status = (WEXITSTATUS(status) / 256);
	else if (WIFSIGNALED(status))
	{
		printf("entered!\n");
		return (128 + WTERMSIG(status));
	}
	return (g.g_status);
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
				restart_fd(d);
				continue ;
			}
			g.g_status = exec_piped_cmd(d, cmd_array[i], i);
		}
	}
	else
	{
		while (++i < (nr_pipes + 1))
		{
			if (only_redirs(cmd_array[i]))
			{
				set_fd_names(d, cmd_array[i]);
				restart_fd(d);
				continue ;
			}
			g.g_status =  exec_piped_cmd(d, cmd_array[i], i);
		}
	}
	unlink(".heredoc");
}

void	executor(t_data *d, t_tokens *t)
{
	int			i;
	char		*tmp;
	t_tokens	**cmd_array;

	i = -1;
	tmp = get_env(d->envars_list, "PATH");
	d->bin_paths = ft_split(tmp, ':');
	free(tmp);
	d->nr_pipes = count_pipes(t);
	cmd_array = NULL;
	if (t->token == e_var)
		do_export(d->envars_list, t->str);
	else if (!commands_tokens(t))
		return ;
	else if (d->nr_pipes > 0)
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
