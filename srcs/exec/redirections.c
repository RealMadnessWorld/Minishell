#include "../../includes/minishell.h"

int	handle_fd(t_data *d, t_tokens *t)
{
	set_fd_names(d, t);
	if (!open_fd(d))
	{
		printf("bro, idk what happened BUTT I cant find that file...\n");
		printf("maybe you have virtual 🐀 in your computer?\n");
		return (0);
	}
	return (1);
	d->fd.weirdoc = 0;
	d->fd.append = 0;
}

int	open_fd(t_data *d)
{
	if (d->fd.out_name)
		return (choose_out(d));
	if (d->fd.in_name)
	{
	}
	return (1);
}

int	choose_out(t_data *d)
{
	if (d->fd.append == 0)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (d->fd.out == -1)
			return (0);
		d->fd.out_original = dup(STDOUT_FILENO);
		dup2(d->fd.out, STDOUT_FILENO);
	}
	if (d->fd.append == 1)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (d->fd.out == -1)
			return (0);
		d->fd.out_original = dup(STDOUT_FILENO);
		dup2(d->fd.out, STDOUT_FILENO);
	}
	return (1);
}

int	choose_in(t_data *d)
{
	if (d->fd.weirdoc == 0)
	{
		d->fd.in = open(d->fd.in_name, O_RDONLY);
		if (d->fd.in == -1)
			return (0);
		d->fd.in_original = dup(STDIN_FILENO);
		dup2(d->fd.in, STDIN_FILENO);
	}
	return 1;
}

static int	its_redir(t_tokens *t)
{
	t_tokens *tmp;

	tmp = t;

	while (tmp && tmp->token != e_pipe)
	{
		if (tmp->token == e_smaller || tmp->token == e_bigger ||
			tmp->token == e_double_bigger)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void trim_redir(char **cmd)
{
    int i;

    i = 0;
    while(cmd[i])
    {
        if (*cmd[i] == '<' || *cmd[i] == '>')
        {
            while(cmd[i])
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
	return (NULL);
}

void	execve_handler(t_data *d, t_tokens *t, t_exec *x)
{
	x = check_cmd(d, t);
	if (x == NULL)
		exit(throw_error(t->str, 127));
	if (its_redir(t))
	{
		handle_fd(d, t);
		trim_redir(x->t);
		execve(x->path, x->t, x->env);
	}
	execve(x->path, x->t, x->env);
}
