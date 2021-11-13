#include "../../includes/minishell.h"

void	be_free_my_child(t_tokens *lst)
{
	t_tokens	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}