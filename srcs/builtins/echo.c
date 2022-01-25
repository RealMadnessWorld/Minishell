/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:28:28 by fmeira            #+#    #+#             */
/*   Updated: 2021/12/30 18:29:01 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	do_the_echo(t_tokens *t)
{
	bool	n;

	n = false;
	if (ft_strcmp(t->str, "echo") == 0)
	{
		t = t->next;
		if (ft_strcmp(t->str, "-n") == 0)
		{
			n = true;
			t = t->next;
		}
		while (t)
		{
			if (t->token == e_pipe || !redirections_tokens(t))
				break ;
			ft_putstr_fd(t->str, 1);
			if (t->next && t->next->token != e_pipe)
				write(1, " ", 1);
			t = t->next;
		}
	}
	return (n);
}

int	echo_fun(t_tokens *t)
{
	bool	n;

	n = false;
	if (g_g.echo == 0)
		n = do_the_echo(t);
	if (n == false)
		write(1, "\n", 1);
	return (0);
}
