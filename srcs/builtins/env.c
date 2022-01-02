/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:29:29 by fmeira            #+#    #+#             */
/*   Updated: 2021/12/30 18:29:44 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_env(t_envars *lst)
{
	t_envars	*elist;

	elist = lst;
	while (elist)
	{
		if (elist->value)
			printf("%s=%s\n", elist->key, elist->value);
		elist = elist->next;
	}
	return (0);
}
