#include "../../includes/minishell.h"

int	set_fd_names(t_data *d, t_tokens *t)
{
	t_tokens *tmp;

	tmp = t;
	while (tmp && tmp->token != e_pipe)
	{
		if (tmp->token == e_smaller)
		{
			if (!do_red_smaller(d, tmp))
				return (0);
		}
		else if (tmp->token == e_bigger)
		{
			if (!do_red_bigger(d,tmp))
				return (0);
		}
		else if (tmp->token == e_double_smaller)
		{
			if (!do_red_weirdoc(d, tmp))
				return (0);
		}
		else if (tmp->token == e_double_bigger)
		{
			if (!do_red_append(d, tmp))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}


int	check_fd_already_redin(t_data *d)
{
	if (d->fd.i_in != 0)
	{
		d->fd.in = open(d->fd.in_name, O_WRONLY | O_CREAT, 0777);
		if (d->fd.in == -1)
		{
			printf("couldn't open that fila mate... sorry (not really)\n");
			return (0);
		}
		close(d->fd.in);
	}
	d->fd.i_in++;
	return (1);
}

int	check_fd_already_redout(t_data *d)
{
	if (d->fd.i_out != 0)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (d->fd.in == -1)
		{
			printf("couldn't open that fila mate... sorry (not really)\n");
			return (0);
		}
		close(d->fd.out);
	}
	d->fd.i_out++;
	return (1);
}

int	check_fd_already_append(t_data *d)
{
	if (d->fd.i_out != 0)
	{
		d->fd.out = open(d->fd.out_name, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (d->fd.in == -1)
		{
			printf("couldn't open that fila mate... sorry (not really)\n");
			return (0);
		}
		close(d->fd.out);
	}
	d->fd.i_out++;
	return (1);
}

void	restart_fd(t_data *d)
{
	if (d->fd.in_name != NULL)
	{
		free(d->fd.in_name);
		dup2(d->fd.in_original, 0);
		close(d->fd.in_original);
		close(d->fd.in);
		d->fd.in_name = NULL;
		d->fd.in_original = -1;
		d->fd.in_original = -1;
	}
	if (d->fd.out_name)
	{
		free(d->fd.out_name);
		dup2(d->fd.out_original, 1);
		close(d->fd.out_original);
		close(d->fd.out);
		d->fd.out_name = NULL;
		d->fd.out_original = -1;
		d->fd.out_original = -1;
	}
}
