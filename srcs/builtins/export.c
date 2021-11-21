#include "../../includes/minishell.h"

void	do_export(t_envars *lst, char *to_add)
{
	t_envars	*curr;
	t_envars	*prev;
	char		**new;

	curr = lst;
	prev = curr;
	if (!to_add)
	{
		do_env(lst);
		return ;
	}
	new = set_line(to_add);
	while (curr)
	{
		if (!(ft_strcmp(curr->key, new[0])))
		{
			free(curr->value);
			curr->value = new[1];
			free(new[0]);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	prev->next = add_node(new);
}
