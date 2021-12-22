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

int	throw_error(char *str, int err)
{
	if (err == 127)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		g.g_status = 127;
		return (127);
	}
	if (err == 255)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g.g_status = 255;
		return (255);
	}
	if (err == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": argument supplied is not valid\n", 2);
		g.g_status = 1;
		return (1);
	}
	g.g_status = 1;
	return (1);
}
