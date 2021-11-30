#include "../../includes/minishell.h"

static void	ctrl_c_handler()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	do_i_have_signal()
{
	struct sigaction ctrl_c;
	struct sigaction ctrl_barra;

	ctrl_c.sa_flags = SA_RESTART;
	ctrl_c.sa_handler = &ctrl_c_handler;
	sigaction(SIGINT, &ctrl_c, NULL);
	ctrl_barra.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ctrl_barra, NULL);
}