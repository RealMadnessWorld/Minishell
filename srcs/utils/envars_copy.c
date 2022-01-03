/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envars_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:41:43 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/03 17:45:05 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envars	*copy_envars(t_envars *t)
{
	t_envars	*copy;

	copy = NULL;
	while (t)
	{
		env_add_lst(&copy, env_new(t->key, t->value));
		t = t->next;
	}
	return (copy);
}

t_envars	*env_last(t_envars *t)
{
	if (!t)
		return (NULL);
	while (t)
	{
		if (t->next == NULL)
			return (t);
		t = t->next;
	}
	return (t);
}

t_envars	*env_new(char *key, char *value)
{
	t_envars	*novo;

	novo = (t_envars *)malloc(sizeof(t_envars));
	novo->key = key;
	novo->value = value;
	novo->next = NULL;
	return (novo);
}

void	env_add_lst(t_envars **t, t_envars *new)
{
	t_envars	*tmp;

	tmp = env_last(*t);
	if (!*t)
	{
		*t = new;
		return ;
	}
	tmp->next = new;
}

char	*expand_exit_status(char *str, int start, int end)
{
	char	*str_to_fit;
	char	*new;
	int		i;
	int		j;

	str_to_fit = ft_itoa(g_g.status);
	j = -1;
	i = ((ft_strlen(str) - (end - start)) + ft_strlen(str_to_fit));
	new = ft_calloc(++i, sizeof(char));
	i = -1;
	while (++i < start)
		new[i] = str[i];
	while (++j < (int)ft_strlen(str_to_fit))
		new[i++] = str_to_fit[j];
	j = ++end;
	while (j < (int)ft_strlen(str))
		new[i++] = str[j++];
	free(str_to_fit);
	str_to_fit = ft_strdup(new);
	free(new);
	new = NULL;
	return (str_to_fit);
}
