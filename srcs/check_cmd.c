#include "minishell.h"

int	check_cmd(char *str, t_cmd *d)
{
	// if (str == "cd")
	// 	return (/*deal with cd*/);
	// if (str == "echo")
	// 	return (/*deal with echo*/);
	// if (str == "pwd")
	// 	return (/*deal with pwd*/);
	// if (str == "export")
	// 	return (/*deal with export*/);
	// if (str == "unset")
	// 	return (/*deal with unset*/);
	// if (str == "env")
	// 	return (/*deal with env*/);
	if (ft_strncmp(str, "exit", 4) == 0)
		exit_func(d);
	return (0);
}