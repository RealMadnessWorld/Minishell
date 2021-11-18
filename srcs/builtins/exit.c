#include "../../includes/minishell.h"

void	exit_func(t_data *d)
{
	rl_clear_history();
	everyone_be_freeee(d);
	printf(CLR_CYN"Bye daddy! Have a great day! 🖤🖤🖤\n"CLR_RST);
	exit(EXIT_SUCCESS);
}
