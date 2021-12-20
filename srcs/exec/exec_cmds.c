#include "../../includes/minishell.h"

static t_exec	*check_cmd(t_data *d, t_tokens *t)
{
	int		i;
	int		invalid;
	t_exec	*x;

	i = 0;
	x = malloc(sizeof(t_exec));
	if (!(access(t->str, F_OK)))
	{
		x->path = t->str;
		x->env = conv_env(d->envars_list);
		x->t = conv_tokens(t);
		return (x);
	}
	while (d->bin_paths[i] != NULL)
	{
		x->path = ft_strjoin_path(d->bin_paths[i], "/", t->str);
		invalid = access(x->path, F_OK);
		if (!invalid)
		{
			x->env = conv_env(d->envars_list);
			x->t = conv_tokens(t);
			return (x);
		}
		free(x->path);
		i++;
	}
	return NULL;
}

static int	exec_cmd(t_data *d, t_tokens *t)
{
	t_exec	*x;
	pid_t	pid;
	int		status;

	x = NULL;
	if (t->token == e_command)
		g_status = do_builtin(d, t);
	else
	{
		x = check_cmd(d, t);
		if (x == NULL)
			return (throw_error(t->str, 127));
		pid = fork();
		if (pid == 0)
			execve(x->path, x->t, x->env);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
       			g_status = WEXITSTATUS(status);
			close_pipes(d->nr_pipes, d->pipes, -1, x);
		}
	}
	return (g_status);
}

static int	exec_piped_cmd(t_data *d, t_tokens *t, int pipe_pos)
{
	t_exec	*x;
	pid_t	pid;
	int		status;

	x = NULL;
	pid = fork();
	if (pid == 0)
	{
		manage_input_output(d->nr_pipes, d->pipes, pipe_pos);
		if (t->token == e_command)
			exit(do_builtin(d, t) * 256);
		else
		{
			x = check_cmd(d, t);
			if (x == NULL)
				exit(throw_error(t->str, 127));
			execve(x->path, x->t, x->env);
		}
		exit(1);
	}
	waitpid(pid, &status, 0);
	close_pipes(d->nr_pipes, d->pipes, pipe_pos, x);
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
			g_status = exec_piped_cmd(d, cmd_array[i], i);
	}
	else
	{
		while (++i < (nr_pipes + 1))
			g_status =  exec_piped_cmd(d, cmd_array[i], i);
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
