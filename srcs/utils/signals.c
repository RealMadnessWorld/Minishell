#include "../../includes/minishell.h"

static void	ctrl_c_handler()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	do_i_have_signal(int sig)
{
	if (sig == SIGINT)
		ctrl_c_handler();
	if (sig == SIGQUIT)
		ctrl_c_handler();
}