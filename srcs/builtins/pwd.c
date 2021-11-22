#include "../../includes/minishell.h"

void	do_pwd(t_envars *lst)
{
	t_envars	*curr;

	curr = lst;
	while (curr)
	{
		if (!(ft_strcmp(curr->key, "PWD")))
		{
			printf("%s\n", (curr->value + 1));
			break ;
		}
		curr = curr->next;
	}
}
