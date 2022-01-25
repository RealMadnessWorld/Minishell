/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:59:33 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/25 18:04:02 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_builtin(t_data *d, t_tokens *t)
{
	if (!handle_fd(d, t))
		return (127);
	if (ft_strcmp(t->str, "cd") == 0)
		return (do_cd(t, d->envars_list));
	if (ft_strcmp(t->str, "echo") == 0)
		return (echo_fun(t));
	if (ft_strcmp(t->str, "pwd") == 0)
		return (do_pwd());
	if (ft_strcmp(t->str, "export") == 0)
	{
		if (t->next == NULL || t->next->token == e_pipe)
			return (do_export(d->envars_list, NULL));
		else
			return (export_func(d->envars_list, t));
	}
	if (ft_strcmp(t->str, "unset") == 0)
		return (unset_func(&d->envars_list, t));
	if (ft_strcmp(t->str, "env") == 0)
		return (do_env(d->envars_list));
	if (ft_strcmp(t->str, "exit") == 0)
		exit_func(d, t);
	return (1);
}

void	free_dbl_str(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		line[i++] = NULL;
	}
	free(line[i]);
	line[i] = NULL;
	free(line);
	line = NULL;
}

void	handle_plus(t_tokens *t)
{
	char	*new;

	if (t->next && t->next->str)
	{
		if (!not_int(t->next->str + 1) && *t->next->str == '+')
		{
			new = ft_strdup(t->next->str + 1);
			free(t->next->str);
			t->next->str = new;
		}
	}
}
