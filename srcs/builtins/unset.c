#include "../../includes/minishell.h"

void	unset_func(t_data *d, t_tokens *t)
{
	t_tokens	*curr;

	curr = t->next;
	do_unset(&d->envars_list, t->str);
	while (curr->next && curr->next->token != e_pipe)
	{
		do_unset(&d->envars_list, t->str);
		curr = curr->next;
	}
}

void	do_unset(t_envars **lst, char *to_unset)
{
	t_envars	*curr;
	t_envars	*last;

	curr = *lst;
	last = curr;
	if (!(ft_strcmp(curr->key, to_unset)))
	{
		*lst = curr->next;
		delete(curr);
		return ;
	}
	while (curr)
	{
		if (!(ft_strcmp(curr->key, to_unset)))
		{
			last->next = curr->next;
			delete(curr);
			break ;
		}
		last = curr;
		curr = curr->next;
	}
}
