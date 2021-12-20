#include "../../includes/minishell.h"

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

void	close_pipes(int nr_pipes, int **pipe_fd, int pipe_pos, t_exec *x)
{
	if (x)
	{
		if (x->env)
			free(x->env);
		if (x->path)
			free(x->path);
		if (x->t)
			free(x->t);
	}
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

int	only_redir(t_tokens *t)
{
	int	i;

	i = 0;

	if (t->str[i] == '<' || t->str[i] == '>' ||
		(t->str[i] == '>' && t->str[i + 1] == '>'))
	{
		// handle_fd(d)
		return (1);
	}
	return (0);
}

void	execve_handler(t_data *d, t_tokens *t)
{
	t_exec	*x;
	//start_fd

	x = check_cmd(d, t);
	if (x == NULL)
		exit(throw_error(t->str, 127));
	if (its_redir(x->t))
	{
		if (!handle_fd(d, t))
			return (0);
		x->t = trim_redir(x->t);
		execve(x->path, x->t, x->env);
	}
	execve(x->path, x->t, x->env);
}
