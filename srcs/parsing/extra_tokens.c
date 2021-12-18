#include "../../includes/minishell.h"

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
	t_tokens *tmp;

	tmp = t;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, "echo") == 0)
		{
			if (tmp->next == NULL)
				return (error_zero(CLR_RED"What am I? A mind reader? 👿"CLR_RST));
			tmp = tmp->next;
			if (!echo_parser(tmp))
				return (error_zero(CLR_RED"What am I? A mind reader? 👿"CLR_RST));
		}
		tmp = tmp->next;
	}
	return (1);
}
