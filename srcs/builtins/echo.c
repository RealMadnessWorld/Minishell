#include "../../includes/minishell.h"

void	echo_fun(t_tokens *t)
{
	bool	n;

	n = false;
	if (ft_strcmp(t->str, "echo") == 0)
	{
		t = t->next;
		if (ft_strcmp(t->str, "-n") == 0)
		{
			n = true;
			t = t->next;
		}
		while(t)
		{
			if (t->token == e_pipe || !redirections_tokens(t))
				break;
			ft_putstr_fd(t->str, 1);
			if (t->next && t->next->token != e_pipe)
				write(1, " ", 1);
			t = t->next;
		}
	}
	if (n == false)
		write(1, "\n", 1);
}