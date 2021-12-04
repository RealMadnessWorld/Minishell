#include "../../includes/minishell.h"

void	check_cmd(t_data *d, t_tokens *t)
{
	if (ft_strcmp(t->str, "cd") == 0)
		do_cd(t, d->envars_list);
	if (ft_strcmp(t->str, "echo") == 0)
		echo_fun(t);
	if (ft_strcmp(t->str, "pwd") == 0)
		do_pwd();
	// if (ft_strcmp(t->str, "export") == 0)
	// 	do_export(d->envars_list, t->next->str);
	// if (ft_strcmp(t->str, "unset") == 0)
	// 	do_unset(d->envars_list, t->next->str);
	if (ft_strcmp(t->str, "env") == 0)
		do_env(d->envars_list);
	if (ft_strcmp(t->str, "exit") == 0)
		exit_func(d);
}
