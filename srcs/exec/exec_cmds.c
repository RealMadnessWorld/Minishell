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

	x = NULL;
	if (t->token == e_command)
		do_builtin(d, t);
	else
	{
		x = check_cmd(d, t);
		if (x == NULL)
			return (printf(CLR_RED"I don't know wtf is \"%s\"...🤨\nPlease speak binary!\n"CLR_RST, t->str));
		pid = fork();
		if (pid == 0)
		{
			if (execve(x->path, x->t, x->env) == -1)
    			perror("execve fail");
			exit(0);
		}
		else
			wait(NULL);
	}
	return (0);
}

static int	exec_piped_cmd(t_data *d, t_tokens *t, int pipe_pos)
{
	t_exec	*x;
	pid_t	pid;

	x = NULL;
	pid = fork();
	if (pid == 0)
	{
		manage_input_output(d->nr_pipes, d->pipes, pipe_pos);
		if (t->token == e_command)
			do_builtin(d, t);
		else
		{
			x = check_cmd(d, t);
			if (x == NULL)
				pipe_error(t->str);
			if (execve(x->path, x->t, x->env) == -1)
    			perror("execve fail");
		}
		exit(0);
	}
	else
	{
		wait(&pid);
		close_pipes(d->nr_pipes, d->pipes, pipe_pos, x);
	}
	return (0);
}

void do_pipes(t_tokens **cmd_array, int nr_pipes, t_data *d)
{
	int	i;

	i = -1;
	if (nr_pipes == 1)
	{
		while (++i <= nr_pipes)
		{
			if (exec_piped_cmd(d, cmd_array[i], i))
				break ;
		}
	}
	else
	{
		while (++i < (nr_pipes + 1))
		{
			if (exec_piped_cmd(d, cmd_array[i], i))
				break ;
		}
	}

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
	if (!open_fd(d))
	{
		printf("bro, idk what happened BUTT I cant find that file...\n");
		printf("maybe you have virtual 🐀 in your computer?\n");
		return ;
	}
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
