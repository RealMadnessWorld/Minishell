#include "../../includes/minishell.h"

void	exit_func(t_cmd *d)
{
	free(d->cmdline);
	free(d->str);
	exit(EXIT_SUCCESS);
}

void	do_env(char **envp)
{
    int i = 0;

	while (envp[i])
		printf("%s\n", envp[i++]);
}
<<<<<<< HEAD:srcs/utils.c
=======

// void	do_export(char *str, t_envars **envars_lst)
// {
// 	if (already_on_env)
// 	{

// 	}

// 	else
// 	{
// 		while ()
// 	}
// }
>>>>>>> 129c85138c486eecf7946fb14f1c924436605442:srcs/utils/utils.c
