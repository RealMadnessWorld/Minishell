/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:38:02 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/02 16:39:11 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_fd_names(t_data *d, t_tokens *t)
{
	t_tokens	*tmp;

	tmp = t;
	while (tmp && tmp->token != e_pipe)
	{
		if (!set_tokens(d, tmp))
			return (0);
		tmp = tmp->next;
	}
	d->fd.heredoc_count = 1;
	return (1);
}

int	check_fd_already_redin(t_data *d)
{
	if (d->fd.i_in != 0)
	{
		d->fd.in = open(d->fd.in_name, O_WRONLY);
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
		if (d->fd.out == -1)
		{
			printf("couldn't open that file mate... sorry (not really)\n");
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
			printf("couldn't %s, mate... sorry (not really)\n", d->fd.out_name);
			return (0);
		}
		close(d->fd.out);
	}
	d->fd.i_out++;
	return (1);
}

void	restart_fd(t_data *d)
{
	close_start_fd(d);
	if (d->fd.heredoc_fd != 0)
	{
		d->fd.heredoc_fd = 0;
		dup2(d->fd.in_original, 0);
	}
	d->fd.weirdoc = 0;
	d->fd.i_in = 0;
	d->fd.i_out = 0;
}
