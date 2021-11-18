#include "../../includes/minishell.h"

void	exit_func(t_data *d)
{
	rl_clear_history();
	everyone_be_freeee(d);
	exit(EXIT_SUCCESS);
}
