#include "../../includes/minishell.h"

static void	deal_in_child()
{
	g.g_status = 130;
	if (g.child == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
	return ;
}

void	do_i_have_signal()
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_barra;

	ctrl_c.sa_handler = &deal_in_child;
	ctrl_c.sa_flags = SA_RESTART;
	ctrl_barra.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ctrl_c, NULL);
	sigaction(SIGQUIT, &ctrl_barra, NULL);
	return ;
}
