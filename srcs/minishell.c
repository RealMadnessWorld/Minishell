#include "../includes/minishell.h"

int	main(int ac, char ** av, char **envp)
{
	t_cmd	cmd;
	int		i;

	(void)ac;
	(void)av;
	while (1)
	{
		cmd.str = readline("What is your command?\t\n");
		add_history(cmd.str);
		cmd.cmdline = split(cmd.str, ' ', &cmd);
		i = 0;
		while(i < cmd.i)
			check_cmd(cmd.cmdline[i++], &cmd, envp);
		free(cmd.cmdline);
		free(cmd.str);
	}
}
