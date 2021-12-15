#include "../../includes/minishell.h"

void	set_fd_names(t_data *d, t_tokens *t)
{
	while (t)
	{
		if (t->token == e_smaller)
		{
			if (!t->next)
			{
				printf ("Where is the file you beautiful bastard?\n");
				return ;
			}
			d->fd.in_name = ft_strdup(t->next->str);
			t->next->token = e_fd;
		}
		else if (t->token == e_bigger)
		{
			if (!t->next)
			{
				printf ("Where is the file you beautiful bastard?\n");
				return ;
			}
			d->fd.out_name = ft_strdup(t->next->str);
			t->next->token = e_fd;
		}
		t = t->next;
	}
}

void	restart_fd(t_data *d)
{
	if (d->fd.in_name != NULL)
	{
		free(d->fd.in_name);
		dup2(d->fd.in_original, 0);
		close(d->fd.in_original);
		d->fd.in_name = NULL;
		d->fd.in_original = -1;
		d->fd.in_original = -1;
	}
	if (d->fd.out_name)
	{
		free(d->fd.out_name);
		dup2(d->fd.out_original, 1);
		close(d->fd.out_original);
		d->fd.out_name = NULL;
		d->fd.out_original = -1;
		d->fd.out_original = -1;
	}
}