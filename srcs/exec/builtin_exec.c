#include "../../includes/minishell.h"

int	do_builtin(t_data *d, t_tokens *t)
{
	if (!handle_fd(d, t))
		return (0);
	if (ft_strcmp(t->str, "cd") == 0)
		return (do_cd(t, d->envars_list));
	if (ft_strcmp(t->str, "echo") == 0)
		return (echo_fun(t));
	if (ft_strcmp(t->str, "pwd") == 0)
		return (do_pwd());
	if (ft_strcmp(t->str, "export") == 0)
	{
		if (t->next == NULL || t->next->token == e_pipe)
			return (do_export(d->envars_list, NULL));
		else
			return (export_func(d->envars_list, t));
	}
	if (ft_strcmp(t->str, "unset") == 0)
		return (unset_func(&d->envars_list, t));
	if (ft_strcmp(t->str, "env") == 0)
		return (do_env(d->envars_list));
	if (ft_strcmp(t->str, "exit") == 0)
		exit_func(d, t);
	return (2);
}
