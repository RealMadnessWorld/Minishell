#include "../includes/minishell.h"

int	main(int ac, char ** av, char **envp)
{
	t_cmd	cmd;
	char	*str;
	int		i;

	ac++;
	av++;
	while (1)
	{
		str = readline("What is your command?\t\n");
		add_history(str);
		cmd.cmdline = split(str, ' ', &cmd);
		i = 0;
		while(i < cmd.i)
			check_cmd(cmd.cmdline[i++], &cmd, envp);
		free(cmd.cmdline);
	}
}
