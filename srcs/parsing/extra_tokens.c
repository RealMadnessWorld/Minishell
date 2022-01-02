/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 15:30:51 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/02 16:21:42 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_fd(t_tokens *tmp)
{
	t_tokens	*t;

	t = tmp;
	while (t)
	{
		if (!redirections_tokens(t))
		{
			if (!t->next)
			{
				printf("where is the file you beautiful bastard?\n");
				return (0);
			}
			t->next->token = e_fd;
		}
		t = t->next;
	}
	return (1);
}

int	redirections_char(char *t)
{
	if (ft_strcmp(t, ">") == 0)
		return (0);
	else if (ft_strcmp(t, "<") == 0)
		return (0);
	else if (ft_strcmp(t, ">>") == 0)
		return (0);
	else if (ft_strcmp(t, "<<") == 0)
		return (0);
	return (1);
}

int	redirections_tokens(t_tokens *t)
{
	if (ft_strcmp(t->str, ">") == 0)
		return (0);
	else if (ft_strcmp(t->str, "<") == 0)
		return (0);
	else if (ft_strcmp(t->str, ">>") == 0)
		return (0);
	else if (ft_strcmp(t->str, "<<") == 0)
		return (0);
	return (1);
}

int	echo_parser(t_tokens *t)
{
	t_tokens	*tmp;

	tmp = t;
	if (tmp->token != e_pipe)
	{
		while (tmp)
		{
			if (tmp->token == e_pipe || !redirections_tokens(t))
				return (1);
			tmp->token = e_echo_print;
			tmp = tmp->next;
		}
	}
	else
		return (0);
	return (1);
}

int	commands_tokens(t_tokens *t)
{
	t_tokens	*tmp;
	char		*arsenio;

	tmp = t;
	arsenio = CLR_RED"What am I? A mind reader? 👿"CLR_RST;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, "echo") == 0)
		{
			if (tmp->next == NULL)
				return (error_zero(arsenio));
			tmp = tmp->next;
			if (!echo_parser(tmp))
				return (error_zero(arsenio));
		}
		tmp = tmp->next;
	}
	return (1);
}
