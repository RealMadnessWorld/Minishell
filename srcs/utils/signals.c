#include "../../includes/minishell.h"

static void	ctrl_c_handler()
{
	// int	in = open("input", O_RDONLY);
	// dup2(in, STDIN_FILENO);
	// close(in);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// static void	ctrl_d_handler()
// {

// }

void	do_i_have_signal()
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_barra;
	// struct sigaction	ctrl_d;

	// ctrl_d.sa_handler = &ctrl_d_handler;
	ctrl_c.sa_handler = &ctrl_c_handler;
	ctrl_c.sa_flags = SA_RESTART;
	ctrl_barra.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ctrl_c, NULL);
	sigaction(SIGQUIT, &ctrl_barra, NULL);
}
