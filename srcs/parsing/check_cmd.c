#include "../../includes/minishell.h"

int	check_cmd(char *str, t_data *d, char **envp)
{
	// if (str == "cd")
	// 	return (/*deal with cd*/);
	// if (str == "echo")
	// 	return (/*deal with echo*/);
	// if (str == "pwd")
	// 	return (/*deal with pwd*/);
	// if (str == "export")env

	// 	return (/*deal with export*/);
	// if (str == "unset")
	// 	return (/*deal with unset*/);
	if (ft_strcmp(str, "env") == 0)
		do_env(envp);
	if (ft_strcmp(str, "exit") == 0)
		exit_func(d);
	return (0);
}

