#include "../../includes/minishell.h"

void	do_export(t_envars *lst, char *to_add)
{
	t_envars	*curr;
	t_envars	*prev;
	char		*new;

	curr = lst;
	prev = curr;
	if (!to_add)
	{
		do_env(lst);
		return ;
	}
	new = ft_strdup(to_add);
	while (curr)
	{
		if (!(ft_strcmp(curr->key, to_add)))
		{
			free(curr->value);
			curr->value = new;
		}
		prev = curr;
		curr = curr->next;
	}
	prev->next = add_node(set_line(new));
}
