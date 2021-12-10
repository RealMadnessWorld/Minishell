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

static void	free_cmd(t_cmd *cmd)
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
			cmd->cmdline = NULL;
		}
	}
}

int	everyone_be_freeee(t_data *d)
{
	int	i;

	i = 0;
	be_free_my_child(d->t);
	free_cmd(&d->cmd);
	if (d->cmd.str)
		free(d->cmd.str);
	if (d->pipes)
	{
		while (i < d->nr_pipes)
			free(d->pipes[i++]);
		free(d->pipes);
		d->pipes = NULL;
	}
	return (1);
}

void	free_envars_list(t_envars *env)
{
	t_envars	*curr;

	curr = env;
	if (curr)
	{
		while (curr)
		{
			free(curr->key);
			free(curr->value);
			curr = curr->next;
		}
	}
	free(env);
	env = NULL;
}
