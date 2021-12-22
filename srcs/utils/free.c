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
			free(tmp);
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
			}
			free(cmd->cmdline);
		}
	}
}

int	everyone_be_freeee(t_data *d)
{
	int	i;

	i = 0;
	if (d->cmd.str != NULL)
	{
		be_free_my_child(d->t);
		free_cmdline(&d->cmd);
		clear_paths(d);
		if (d->cmd.str)
			free(d->cmd.str);
	}
	return (1);
}

void	free_envars_list(t_envars *env)
{
	t_envars	*curr;

	if (env)
	{
		while (env)
		{
			curr = env;
			if (curr->key)
				free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			env = env->next;
		}
	}
	// free(env);
}

void free_pipes(t_data *d)
{
	int	i;

	i = -1;
	while(++i < d->nr_pipes)
	{
		if (d->pipes[i])
			free(d->pipes[i]);
	}
	free(d->pipes);
}
