#include "../../includes/minishell.h"

void	be_free_my_child(t_tokens *lst)
{
	t_tokens	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->str);
		free(tmp);
	}
}

static void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmdline[i])
	{
		free(cmd->cmdline[i]);
		cmd->cmdline[i] = NULL;
	}
	free(cmd->cmdline);
	cmd->cmdline = NULL;
}

void	everyone_be_freeee(t_data *d)
{
	int	i;

	i = -1;
	be_free_my_child(d->t);
	free_cmd(&d->cmd);
	free(d->cmd.str);
	if (d->pipes)
	{
		while (d->pipes[++i])
			free(d->pipes[i]);
		free(d->pipes);
		d->pipes = NULL;
	}
}
