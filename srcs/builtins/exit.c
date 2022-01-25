/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:30:02 by fmeira            #+#    #+#             */
/*   Updated: 2022/01/25 18:03:47 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long long	ft_stoi(char *str)
{
	long long	signal;
	long long	result;
	char		*p;

	p = (char *)str;
	signal = 1;
	result = 0;
	while (*p == ' ' || *p == '\t' || *p == '\n'
		|| *p == '\r' || *p == '\v' || *p == '\f')
		p++;
	if (*p == '+')
		p++;
	else if (*p == '-')
	{
		p++;
		signal = -1;
	}
	while (*p > 47 && *p < 58)
		result = result * 10 + *p++ - 48;
	result = result * signal;
	return (result);
}

static int	not_int(char *s)
{
	int			i;
	int			len;
	char		*tmp;
	long long	check_size;
	long long	max_int;

	if (s && *s)
	{
		i = 0;
		len = ft_strlen(s);
		tmp = s;
		check_size = ft_stoi(tmp);
		max_int = 2147483647;
		if (check_size > max_int)
			return (1);
		if (s[i] == '-' && ft_isdigit(s[1]))
			i++;
		while (i < len)
		{
			if (!(ft_isdigit(s[i++])))
				return (1);
		}
	}
	return (0);
}

int	throw_error(char *str, int err)
{
	if (err == 127)
	{
		print_error(str, ": command not found\n");
		g_g.status = 127;
		return (127);
	}
	if (err == 255)
	{
		print_error(str, ": numeric argument required\n");
		g_g.status = 255;
		return (255);
	}
	if (err == 1)
	{
		print_error(str, ": argument supplied is not valid\n");
		g_g.status = 1;
		return (1);
	}
	g_g.status = 1;
	return (1);
}

void	exit_func(t_data *d, t_tokens *t)
{
	int		exit_nbr;

	exit_nbr = 0;
	handle_plus(t);
	if (d->cmd.str != NULL && t->next && t->next->str && *t->next->str != '|')
	{
		if (not_int((t->next->str)))
			exit_nbr = throw_error("exit", 255);
		else if (t->next->next && *t->next->next->str != '|')
		{
			g_g.status = throw_error("exit", 1);
			return ;
		}
		else if ((ft_atoi(t->next->str)) > 255)
			exit_nbr = (ft_atoi(t->next->str)) % 256;
		else
			exit_nbr = ft_atoi(t->next->str);
		clear_history();
	}
	everyone_be_freeee(d);
	printf(CLR_CYN"Bye daddy! Have a great day! 🖤🖤🖤\n"CLR_RST);
	exit(exit_nbr);
}

void	clear_paths(t_data *d)
{
	int	i;

	i = -1;
	while (d->bin_paths[++i])
		free(d->bin_paths[i]);
	free(d->bin_paths);
	d->bin_paths = NULL;
}
