/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:57:39 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/02 18:58:01 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	deal_in_child()
{
	// g.g_status = 130;
	if (g_g.child == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	do_i_have_signal()
{
	signal(SIGINT, &deal_in_child);
	signal(SIGQUIT, SIG_IGN);
	return ;
}
