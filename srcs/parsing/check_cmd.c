#include "../../includes/minishell.h"

int	check_cmd(t_data *d, t_tokens *t)
{
	// if (str == "cd")
		// return (/*deal with cd*/);
	if (ft_strcmp(t->str, "echo") == 0)
		echo_fun(t);
	// if (str == "pwd")
	// 	return (/*deal with pwd*/);
	// if (str == "export")env
	// 	return (/*deal with export*/);
	// if (str == "unset")
	// 	return (/*deal with unset*/);
	if (ft_strcmp(t->str, "env") == 0)
		env_print(d);
	if (ft_strcmp(t->str, "exit") == 0)
		exit_func(d);
	return (0);
}

