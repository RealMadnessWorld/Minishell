#include "../../includes/minishell.h"

static int	its_redir(t_tokens *t)
{
	t_tokens *tmp;

	tmp = t;

	while (tmp && tmp->token != e_pipe)
	{
		if (tmp->token == e_smaller || tmp->token == e_bigger ||
			tmp->token == e_double_bigger || tmp->token == e_double_smaller)
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
	free(x);
	return (NULL);
}

void	execve_handler(t_data *d, t_tokens *t)
{
	t_exec	*x;

	if (!d->bin_paths)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(t->str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	x = check_cmd(d, t);
	if (x == NULL)
		exit(throw_error(t->str, 127));
	if (its_redir(t))
	{
		if (!handle_fd(d, t))
			exit(127);
		trim_redir(x->t);
		execve(x->path, x->t, x->env);
	}
	execve(x->path, x->t, x->env);
}
