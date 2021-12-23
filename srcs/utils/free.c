#include "../../includes/minishell.h"

void	be_free_my_child(t_tokens *lst)
{
	t_tokens	*tmp;

	if (lst)
	{
		while (lst != NULL)
		{
			tmp = lst;
			lst = lst->next;
			free(tmp->str);
			tmp->next = NULL;
			free(tmp);
			tmp = NULL;
		}
	}
}

static void	free_cmdline(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd)
	{
		if (cmd->cmdline)
		{
			while (cmd->cmdline[++i])
			{
				free(cmd->cmdline[i]);
				cmd->cmdline[i] = NULL;
			}
			free(cmd->cmdline);
			cmd ->cmdline = NULL;
		}
	}
	cmd = NULL;
}

int	everyone_be_freeee(t_data *d)
{
	int	i;

	i = 0;
	if (d->cmd.str != NULL)
	{
		be_free_my_child(d->t);
		free_cmdline(&d->cmd);
		if (d->bin_paths)
			clear_paths(d);
		if (d->cmd.str)
			free(d->cmd.str);
		d->cmd.str = NULL;
	}
	if (d->fd.in_name != NULL)
	{
		free(d->fd.in_name);
		d->fd.in_name = NULL;
	}
	if (d->fd.out_name != NULL)
	{
		free(d->fd.out_name);
		d->fd.out_name = NULL;
	}
	return (1);
}

void	free_envars_list(t_envars *env)
{
	t_envars	*curr;
	t_envars	*last;

	curr = env;
	if (env)
	{
		while (curr)
		{
			last = curr;
			if (last->key)
				free(last->key);
			if (last->value)
				free(last->value);
			curr = curr->next;
			free(last);
			last = NULL;
		}
	}
	free(env);
	env = NULL;
}

void	free_pipes(t_data *d)
{
	int	i;

	if (d->nr_pipes > 0)
	{
		i = -1;
		while (++i < d->nr_pipes)
		{
			if (d->pipes[i])
				free(d->pipes[i]);
		}
		free(d->pipes);
		d->pipes = NULL;
	}
}
