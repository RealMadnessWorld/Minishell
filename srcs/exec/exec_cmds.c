#include "../../includes/minishell.h"

static void	manage_input_output(int nr_pipes, int **pipe_fd, int pipe_pos)
{
	if (pipe_pos > -1)
	{
		if (pipe_pos == 0)
		{
			close(pipe_fd[pipe_pos][0]);
			dup2(pipe_fd[pipe_pos][1], 1);
		}
		else if (pipe_pos > 0 && (pipe_pos < nr_pipes - 1))
		{
			close(pipe_fd[pipe_pos][0]);
			dup2(pipe_fd[pipe_pos - 1][0], 0);
			dup2(pipe_fd[pipe_pos][1], 1);
		}
		else if (pipe_pos == nr_pipes - 1)
		{
			close(pipe_fd[pipe_pos][1]);
			close(pipe_fd[pipe_pos][0]);
			dup2(pipe_fd[pipe_pos - 1][0], 0);
		}
	}
}

static void	close_pipes(int nr_pipes, int **pipe_fd, int pipe_pos, t_exec *x)
{
	wait(NULL);
	if (x)
	{
		if (x->env)
			free(x->env);
		if (x->path)
			free(x->path);
		if (x->t)
			free(x->t);
	}
	if (pipe_pos > -1)
	{
		if (pipe_pos == 0)
			close (pipe_fd[pipe_pos][1]);
		else if (pipe_pos > 0 && pipe_pos < (nr_pipes - 1))
			close(pipe_fd[pipe_pos][1]);
		else if (pipe_pos == nr_pipes)
		{
			close(pipe_fd[pipe_pos][1]);
			close(pipe_fd[pipe_pos][0]);
		}
	}
}

static t_exec	*check_cmd(t_data *d, t_tokens *t)
{
	int		i;
	int		invalid;
	t_exec	*x;

	i = 0;
	x = malloc(sizeof(t_exec));
	if (t->token == e_command)
		return NULL;
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

static int	exec_cmd(t_data *d, t_tokens *t, int pipe_pos)
{
	int		i;
	t_exec	*x;
	pid_t	pid;

	i = 0;
	x = check_cmd(d, t);
	if (x == NULL && t->token != e_command)
	{
		printf("bash: %s: command not found\n", t->str);
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		manage_input_output(d->nr_pipes, d->pipes, pipe_pos);
		if (t->token == e_command)
		{
			do_builtin(d, t);
			return (0);
		}
		else if (x)
			execve(x->path, x->t, x->env);
	}
	close_pipes(d->nr_pipes, d->pipes, pipe_pos, x);
	return (0);
}

void	executor(t_data *d, t_tokens *t)
{
	int			i;
	t_tokens	**cmd_array;

	i = 0;
	d->bin_paths = ft_split(get_env(d->envars_list, "PATH"), ':');
	d->nr_pipes = count_pipes(t);
	cmd_array = NULL;
	if (d->nr_pipes > 0)
		cmd_array = conv_cmds(t, d->nr_pipes);
	if (!commands_tokens(t))
		return ;
	if (d->nr_pipes)
	{
		d->pipes = malloc(sizeof(int *) * d->nr_pipes);
		while (i < d->nr_pipes)
		{
			d->pipes[i] = malloc(sizeof(int) * 2);
			pipe(d->pipes[i++]);
		}
		i = -1;
		while (++i < d->nr_pipes)
			exec_cmd(d, cmd_array[i], i);
	}
	else
		exec_cmd(d, t, -1);
}
