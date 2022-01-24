/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:57:39 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/02 23:35:21 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	deal_in_child(int sig)
{
	sig = 130;
	if (g_g.child == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_g.status = sig;
	}
	return ;
}

static void	ignore(int dummy)
{
	dummy = g_g.status;
	g_g.status = dummy;
}

void	do_i_have_signal(void)
{
	signal(SIGINT, &deal_in_child);
	signal(SIGQUIT, &ignore);
	return ;
}
