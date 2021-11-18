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
