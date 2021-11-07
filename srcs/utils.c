#include "../includes/minishell.h"

void	exit_func(t_cmd *d)
{
	free(d->cmdline);
	free(d->str);
	exit(EXIT_SUCCESS);
}
