#include "../../includes/minishell.h"

t_tokens	*token_lstnew(char *content)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new)
		return (0);
	new->str = content;
	new->next = NULL;
	return (new);
}

t_tokens	*token_lstlast(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	token_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*temp;

	if (!new)
		return ;
	temp = token_lstlast(*lst);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp->next = new;
}

int	token_lstsize(t_tokens *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}