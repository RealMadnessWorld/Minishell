/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:59:02 by fmeira            #+#    #+#             */
/*   Updated: 2021/12/30 18:59:02 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_unset(t_envars **lst, char *to_unset)
{
	t_envars	*curr;
	t_envars	*last;

	curr = *lst;
	last = curr;
	if (!(ft_strcmp(curr->key, to_unset)))
	{
		*lst = curr->next;
		delete(curr);
		return ;
	}
	while (curr)
	{
		if (!(ft_strcmp(curr->key, to_unset)))
		{
			last->next = curr->next;
			delete(curr);
			break ;
		}
		last = curr;
		curr = curr->next;
	}
}

int	unset_func(t_envars **env, t_tokens *t)
{
	t_tokens	*curr;

	curr = t->next;
	do_unset(env, curr->str);
	while (curr && curr->token != e_pipe)
	{
		do_unset(env, curr->str);
		curr = curr->next;
	}
	return (0);
}
