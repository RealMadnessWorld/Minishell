#include "../../includes/minishell.h"

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
