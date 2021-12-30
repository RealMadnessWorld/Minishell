#include "../../includes/minishell.h"

void	add(t_tokens *old, char *new)
{
	if (old && old->str)
	{
		free(old->str);
		old->str = NULL;
		old->str = new;
	}
}

void	delete(t_envars *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		free(node);
		node = NULL;
	}
}

int	error_zero(char *error)
{
	ft_putendl_fd(error, 1);
	return (0);
}

int	print_error(char *str, char *errmsg)
{
	ft_putstr_fd("bash: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(errmsg, 2);
	return (1);
}

void	delete_x(t_exec	*x)
{
	int	i;

	i = 0;
	while (x->env[i])
	{
		free(x->env[i]);
		x->env[i] = NULL;
		i++;
	}
	free(x->env[i]);
	free(x->env);
	x->env = NULL;
	i = 0;
	while (x->t[i])
	{
		free(x->t[i]);
		x->t[i] = NULL;
		i++;
	}
	free(x->t[i]);
	free(x->t);
	x->t = NULL;
	free(x);
	x = NULL;
}
