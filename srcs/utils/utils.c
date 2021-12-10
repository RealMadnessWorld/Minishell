#include "../../includes/minishell.h"

void	add(t_tokens *old, char *new)
{
	free(old->str);
	old->str = NULL;
	old->str = new;
}

void	delete(t_envars *node)
{
		free(node->key);
		free(node->value);
		free(node);
		node = NULL;
}

int	error_zero(char *error)
{
	ft_putendl_fd(error, 1);
	return (0);
}
