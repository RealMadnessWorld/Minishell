#include "../../includes/minishell.h"

void	exit_func(t_data *d)
{
	everyone_be_freeee(d);
	exit(EXIT_SUCCESS);
}

void	do_env(char **envp)
{
    int i = 0;

	while (envp[i])
		printf("%s\n", envp[i++]);
}

void	add(t_tokens *old, char *new)
{
	free(old->str);
	old->str = NULL;
	old->str = new;
}
