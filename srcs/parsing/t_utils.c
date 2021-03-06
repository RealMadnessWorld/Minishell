/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:39:31 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/02 16:39:32 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokens	*token_lstnew(char *content)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new)
		return (0);
	new->str = content;
	new->next = NULL;
	return (new);
}

t_tokens	*token_lstlast(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	token_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*temp;

	if (!new)
		return ;
	temp = token_lstlast(*lst);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp->next = new;
}

int	env_lstsize(t_envars *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	set_tokens(t_data *d, t_tokens *t)
{
	t_tokens	*tmp;

	tmp = t;
	if (tmp->token == e_smaller)
	{
		if (!do_red_smaller(d, tmp))
			return (0);
	}
	else if (tmp->token == e_bigger)
	{
		if (!do_red_bigger(d, tmp))
			return (0);
	}
	else if (tmp->token == e_double_smaller && d->fd.heredoc_count == 1)
	{
		if (!do_red_weirdoc(d, tmp))
			return (0);
	}
	else if (tmp->token == e_double_bigger)
	{
		if (!do_red_append(d, tmp))
			return (0);
	}
	return (1);
}
