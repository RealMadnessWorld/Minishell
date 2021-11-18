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
		// printf("what is me? %s\n", t->str)
		if (t->token == e_quotes || t->token == e_single_quotes)
			ft_putstr_fd(t->str, 1);
	}
	if (n == false)
		write(1, "\n", 1);
}