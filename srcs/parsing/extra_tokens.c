#include "../../includes/minishell.h"

int	echo_parser(t_tokens *t)
{
	t_tokens	*tmp;

	tmp = t;
	if (tmp->token != e_pipe)
	{
		while (tmp)
		{
			if (tmp->token == e_pipe)
				return (1);
			tmp->token = e_echo_print;
			tmp = tmp->next;
		}
	}
	else
		return (0);
	return (1);
}

int	cd_parser(t_tokens *t)
{
	t_tokens	*tmp;

	tmp = t;
	if (tmp && tmp->token != e_pipe)
	{
		tmp->token = e_cd_path;
		if (tmp->next && tmp->next->token != e_pipe)
			return (0);
	}
	else if (tmp && tmp->token == e_pipe)
	{
		//set home token
	}
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
				return (error_zero("What am I? A mind reader? 👿"));
			tmp = tmp->next;
			if (!echo_parser(tmp))
				return (error_zero("What am I? A mind reader? 👿"));
		}
		tmp = tmp->next;
	}
	return (1);
}
