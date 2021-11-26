#include "../../includes/minishell.h"

// int	verify_logic(t_tokens * t)
// {

// }

static int	verify_words(t_tokens *t)
{
	while (t)
	{
		if (t->token == is_nothing)
		{
			printf(CLR_RED"I don't know wtf is \"%s\"...🤨\nPlease speak binary!\n"CLR_RST, t->str);
			return (0);
		}
		t = t->next;
	}
	return (1);
}

void	validations(t_data *d)
{
	t_tokens *tmp;

	tmp = d->t;
	if (!commands_tokens(tmp))
		return ;
	if (!verify_words(tmp))
		return ;
	tmp = d->t;
	// verify_logic(tmp);
	while(tmp)
	{
		if (tmp->token == e_command)
			check_cmd(d, tmp);
		tmp = tmp->next;
	}
}