#include "minishell.h"

void	exit_func(t_cmd *d)
{
	free(d->cmdline);
	exit(EXIT_SUCCESS);
}
