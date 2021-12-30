/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 20:54:54 by fmeira            #+#    #+#             */
/*   Updated: 2021/12/30 20:54:55 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_red_smaller(t_data *d, t_tokens *tmp)
{
	check_fd_already_redin(d);
	if (!tmp->next)
	{
		g_g.status = 258;
		printf("Where is the file you beautiful bastard?\n");
		return (0);
	}
	d->fd.in_original = dup(STDIN_FILENO);
	if (d->fd.in_name)
		free(d->fd.in_name);
	d->fd.in_name = ft_strdup(tmp->next->str);
	tmp->next->token = e_fd;
	d->fd.weirdoc = 0;
	return (1);
}

int	do_red_bigger(t_data *d, t_tokens *tmp)
{
	check_fd_already_redout(d);
	if (!tmp->next)
	{
		g_g.status = 258;
		printf("Where is the file you beautiful bastard?\n");
		return (0);
	}
	d->fd.out_original = dup(STDIN_FILENO);
	if (d->fd.out_name)
		free(d->fd.out_name);
	d->fd.out_name = ft_strdup(tmp->next->str);
	tmp->next->token = e_fd;
	d->fd.append = 0;
	return (1);
}

int	do_red_weirdoc(t_data *d, t_tokens *tmp)
{
	char	*str;

	d->fd.in_name = ft_strdup(".tmp.heredoc");
	d->fd.heredoc_fd = open(d->fd.in_name, O_RDWR | O_CREAT, 0777);
	if (d->fd.heredoc_fd == -1)
		return (0);
	d->fd.in_original = dup(STDIN_FILENO);
	while (1)
	{
		str = readline("> ");
		write(d->fd.heredoc_fd, str, strlen(str));
		write(d->fd.heredoc_fd, "\n", 1);
		if (ft_strcmp(tmp->next->str, str) == 0)
		{
			free(str);
			d->fd.weirdoc = 1;
			return (1);
		}
		free(str);
	}
	d->fd.weirdoc = 1;
	close(d->fd.heredoc_fd);
	return (1);
}

int	do_red_append(t_data *d, t_tokens *tmp)
{
	check_fd_already_append(d);
	if (!tmp->next)
	{
		g_g.status = 258;
		printf("Where is the file you beautiful bastard?\n");
		return (0);
	}
	d->fd.out_original = dup(STDIN_FILENO);
	if (d->fd.out_name)
		free(d->fd.out_name);
	d->fd.out_name = ft_strdup(tmp->next->str);
	tmp->next->token = e_fd;
	d->fd.append = 1;
	return (1);
}
