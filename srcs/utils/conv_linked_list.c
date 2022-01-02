/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:16:28 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/02 18:41:09 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokens	**conv_cmds(t_tokens *t, int nr_pipes)
{
	t_tokens	*curr;
	int			i;
	t_tokens	**new;

	curr = t;
	i = 0;
	new = (t_tokens **)malloc(sizeof(t_tokens *) * (nr_pipes + 2));
	new[i] = t;
	i++;
	while (curr)
	{
		if (curr->token == e_pipe)
		{
			new[i] = curr->next;
			i++;
		}
		curr = curr->next;
	}
	new[i] = NULL;
	return (new);
}

static int	command_size(t_tokens *lst)
{
	int			i;
	t_tokens	*curr;

	i = 0;
	curr = lst;
	while (curr && curr->token != e_pipe)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

char	**conv_tokens(t_tokens *t)
{
	char		**cmd_lst;
	int			i;
	t_tokens	*curr;

	i = 0;
	cmd_lst = (char **)malloc(sizeof(char *) * (command_size(t) + 1));
	curr = t;
	if (!cmd_lst)
		return (0);
	while (curr && curr->token != e_pipe)
	{
		cmd_lst[i] = ft_strdup(curr->str);
		curr = curr->next;
		i++;
	}
	cmd_lst[i] = NULL;
	return (cmd_lst);
}

char	**conv_env(t_envars *env)
{
	int			i;
	char		**str;
	t_envars	*curr;

	i = 0;
	str = (char **)malloc(sizeof(char *) * (env_lstsize(env) + 1));
	curr = env;
	if (!str)
		return (0);
	while (curr)
	{
		if (curr->value)
			str[i++] = ft_strjoin_path(curr->key, "=", curr->value);
		curr = curr->next;
	}
	str[i] = NULL;
	return (str);
}

void	replace_env(t_envars *old, char **new)
{
	if (old->value)
	{
		free(old->value);
		old->value = ft_strdup(new[1]);
		if (new[0])
			free(new[0]);
		if (new[1])
			free(new[1]);
		free(new);
		new = NULL;
	}
}
